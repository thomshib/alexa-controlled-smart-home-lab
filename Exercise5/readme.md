# Exercise 5 - Connecting NodeMCU with AWS IoT

## Install the following Arduino Libraries
- NTPClient
- PubSubClient

Unzip NTPClient-master & pubsubclient-master libraries mentioned in the folder into your project's library folder.

## Updating NodeMCU Sketch Code
- Open `sensor_pubsub.ino` file in arduino IDE
- Update the config section at the top of this file with the SSID, Password of your WIFI network, Rest API Endpoint details with the AWS endpoint you noted earlier and  
`<THING_NAME>` with the Thing you created in previous exercise
     ````c
     const char *ssid = "<SSID>";
     const char *password = "<PASSWORD>";

     const char *thing_name = "<THING_NAME>";
     const char *AWS_endpoint = "<REST API Endpoint>";

make the above changes in the code OR build on the previous module by including following changes : 

## Include the following packages in your program:
#include "FS.h" 
#include <PubSubClient.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

## Add AWS configuration
const char *thing_name = "<THING_NAME>";
const char *AWS_endpoint = "<REST API Endpoint>";


## Add PubSub client and Wifi Configurations
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

WiFiClientSecure espClient;
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (strcmp(topic, "mysmarthome/turnonred") == 0)
  {
    set_red_led();
  }
  if (strcmp(topic, "mysmarthome/turnonblue") == 0)
  {
    set_blue_led();
  }
  if (strcmp(topic, "mysmarthome/turnongreen") == 0)
  {
    set_green_led();
  }
  if (strcmp(topic, "mysmarthome/turnoff") == 0)
  {
    turn_off_led();
  }
}
PubSubClient client(AWS_endpoint, 8883, callback, espClient); //set  MQTT port number to 8883 as per //standard

## Remove the code block for starting a local web server i.e configure_local_web_server() from setup() .

## Load certificates and configure shadow update

- delay(1000);
  turn_off_led();
  snprintf(shadowTopicUpdate, 50, "$aws/things/%s/shadow/update", thing_name);
  loadCertificates();

- void loadCertificates()
{
  if (!SPIFFS.begin())
  {
    Serial.println("Failed to mount file system");
    return;
  }

  // Load certificate file
  File cert = SPIFFS.open("/cert.der", "r"); //replace cert.crt with your uploaded file name
  if (!cert)
  {
    Serial.println("Failed to open cert file");
  }
  else
    Serial.println("Success to open cert file");

  delay(1000);

  if (espClient.loadCertificate(cert))
    Serial.println("cert loaded");
  else
    Serial.println("cert not loaded");

  // Load private key file
  File private_key = SPIFFS.open("/private.der", "r"); //replace private eith your uploaded file name
  if (!private_key)
  {
    Serial.println("Failed to open private cert file");
  }
  else
    Serial.println("Success to open private cert file");

  delay(1000);

  if (espClient.loadPrivateKey(private_key))
    Serial.println("private key loaded");
  else
    Serial.println("private key not loaded");

  // Load CA file
  File ca = SPIFFS.open("/ca.der", "r"); //replace ca eith your uploaded file name
  if (!ca)
  {
    Serial.println("Failed to open ca ");
  }
  else
    Serial.println("Success to open ca");

  delay(1000);

  if (espClient.loadCACert(ca))
    Serial.println("ca loaded");
  else
    Serial.println("ca failed");
}

## Add following Wifi configuration to interact with certificates with local time.

- Modify this code block in setup_wifi() function:
  
  espClient.setBufferSizes(512, 512);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  timeClient.begin();
  while (!timeClient.update())
  {
    timeClient.forceUpdate();
  }

  espClient.setX509Time(timeClient.getEpochTime());

## Replace the code block for loop() with the following code:

long lastMsg = 0;
char msg[50];
char shadowTopicUpdate[50];
char payload[100];
int value = 0;

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  long now = millis();

  // Publish every one second
  if (now - lastMsg > 1000)
  {
    value = read_temperature();
    lastMsg = now;
    snprintf(msg, 75, "Room Temprature: %ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    snprintf(payload, 75, "{ \"state\":{\"reported\":{\"temperature\":%ld}}}", value);
    //Serial.println(shadowTopicUpdate);
    //Serial.println(payload);
    client.publish(shadowTopicUpdate, payload);
  }
}

## Add reconnect() for reconnecting to PubSub client and subscribing to it.

// Sensors and LED
void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(thing_name))
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //      client.publish("outTopic", "hello world");
      // ... and resubscribe

      client.subscribe("mysmarthome/turnoff");
      client.subscribe("mysmarthome/turnonred");
      client.subscribe("mysmarthome/turnonblue");
      client.subscribe("mysmarthome/turnongreen");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      char buf[256];
      espClient.getLastSSLError(buf, 256);
      Serial.print("WiFiClientSecure SSL error: ");
      Serial.println(buf);
      delay(5000);
    }
  }
}


## Once done with code modification, we need to load certs in Node MCU. 

## Encrypt the certificate files in DER-format using this command:

$ openssl x509 -in xxx-certificate.pem.crt -out cert.der -outform DER 
$ openssl rsa -in xxx-private.pem.key -out private.der -outform DER
$ openssl x509 -in AmazonRootCA1.pem -out ca.der -outform DER

## Copy the DER-format files into a folder called data which sits alongside your Arduino code.

## Upload these certificates using ESP8266FS tool which is attached in the Exercise5 folder.
- Create a "tools" folder inside Arduino folder.
- Download the ESP8266FS zip and extract it into the tools folder.
- Restart your Arduino IDE.
- Under Tools in Arduino IDE, now you should be able to see "ESP8266 Sketch Data Uploader" option.
- Connect your device and click on "ESP8266 Sketch Data Uploader" option to upload certificates to Node MCU.



