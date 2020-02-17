# Exercise 5 - Connecting NodeMCU with AWS IoT

## Burning the AWS Thing Certificates to NodeMCU

- Copy the `certs` folder to the current working directory
- Open terminal and cd to the newly copied `certs` folder
- Use OpenSSL to convert the certificates to `.der` format so they can be understood by NodeMCU board

````
$ openssl x509 -in xxx-certificate.pem.crt -out cert.der -outform DER 
$ openssl rsa -in xxx-private.pem.key -out private.der -outform DER
$ openssl x509 -in AmazonRootCA1.pem -out ca.der -outform DER
````
- Create a directory `data` which sits alongside your Arduino code and copy all the .DER-format files to it
- From the `Tools` menu in Arduino IDE, you should be able to see `ESP8266 Sketch Data Uploader` option
    > __Note__: If you have followed the prerequisites for this lab, you should already have Arduino ESP8266 filesystem uploader installed.
- Ensure the board is connected to your laptop, click `ESP8266 Sketch Data Uploader` option to upload certificates to NodeMCU. 
    > __Note__: The tool automatically detects `data` folder by convention and uploads its contents to the board.


## Updating the sketch to interact with AWS Thing

### Install the following Arduino Libraries
- NTPClient
- PubSubClient

You can install these libraries from Tools > Manage Libraries

### Include the following packages in your program:
````c
#include "FS.h" 
#include <PubSubClient.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
````

### Add AWS configuration
````c
const char *thing_name = "<THING_NAME>";
const char *AWS_endpoint = "<REST API Endpoint>";
````

### Add PubSub client and Wifi Configurations
````c
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
````

### Removing local web server
Remove the code block for starting a local web server which is `configure_local_web_server();` from `setup()` function.

### Load certificates

Inside the `setup()` function add the below code towards the end
````c
 delay(1000);
 turn_off_led();
 snprintf(shadowTopicUpdate, 50, "$aws/things/%s/shadow/update", thing_name);
 loadCertificates();
````
Add the below code towards the end of the file

````c
void loadCertificates()
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
````

### Sync local time for certificate authentication
Add following Wifi configurations to sync local time for certificate authentication

- Modify the code block in `setup_wifi()` function
````c
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
````

### Sending device updates to AWS Thing

Add the following new variable to the sketch
````c
long lastMsg = 0;
char msg[50];
char shadowTopicUpdate[50];
char payload[100];
int value = 0;
````

Update the loop function code as show below to allow updating Shadows with the temperature values
````c
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
````

### Implementing reconnection strategy for pubsub client

Add the following code to the sketch

````c
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
````
