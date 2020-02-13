#include "FS.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

// Update these with values suitable for your network.
int red_pin = 5;
int green_pin = 4;
int blue_pin = 0;
int redStatus = digitalRead(red_pin);
int greenStatus = digitalRead(green_pin);
int blueStatus = digitalRead(blue_pin);

long lastMsg = 0;
char msg[50];
char shadowTopicUpdate[50];
char payload[100];
int value = 0;

/**********************/
const char *ssid = "<SSID>";
const char *password = "<PASSWORD>";

const char *thing_name = "<THING_NAME>";
const char *AWS_endpoint = "<REST API Endpoint>";
/**********************/

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

void setup()
{
  Serial.begin(115200);
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  Serial.setDebugOutput(true);
  setup_wifi();
  delay(1000);
  turn_off_led();
  snprintf(shadowTopicUpdate, 50, "$aws/things/%s/shadow/update", thing_name);
  loadCertificates();
}

void setup_wifi()
{
  // We start by connecting to a WiFi network
  espClient.setBufferSizes(512, 512);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

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
}

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

void set_blue_led()
{
  digitalWrite(red_pin, HIGH);
  digitalWrite(green_pin, HIGH);
  digitalWrite(blue_pin, LOW);
}

void set_green_led()
{
  digitalWrite(red_pin, HIGH);
  digitalWrite(green_pin, LOW);
  digitalWrite(blue_pin, HIGH);
}

void set_red_led()
{
  digitalWrite(red_pin, LOW);
  digitalWrite(green_pin, HIGH);
  digitalWrite(blue_pin, HIGH);
}

void turn_off_led()
{
  digitalWrite(red_pin, HIGH);
  digitalWrite(green_pin, HIGH);
  digitalWrite(blue_pin, HIGH);
}

int read_temperature()
{
  int temp = 23;
  return temp;
}
