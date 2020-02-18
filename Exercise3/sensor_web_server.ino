#include <ESP8266WiFi.h>
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor

// GPIO Pins
int red_pin = 5;
int green_pin = 4;
int blue_pin = 0;

//Set Temperature sensor to read from pin 2 / D4 
#define DHTTYPE DHT11
#define dht_dpin 2
DHT dht(dht_dpin, DHTTYPE);

//declare global variables 
int redStatus = digitalRead(red_pin);
int greenStatus = digitalRead(green_pin);
int blueStatus = digitalRead(blue_pin);
float temperature = 0;
float humidity = 0;

// Update these with values suitable for your network configuratons.
/**********************/
const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";
/**********************/
// Set web server port number to 80
WiFiServer server(80);

void setup_wifi()
{
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to Wifi");
}

void configure_local_web_server()
{
    //Start WiFi server
  server.begin();
  Serial.println("Server started!");

  // Print the IP address
  Serial.print("Use this URL to connect: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void setup() 
{
  dht.begin();
  Serial.begin(115200);
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  setup_wifi();
  configure_local_web_server();
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


void get_led_status(){
  redStatus = digitalRead(red_pin);
  greenStatus = digitalRead(green_pin);
  blueStatus = digitalRead(blue_pin);
}

void get_temperature(){
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE html><html>");

  if (request.indexOf("/RED=ON") != -1)  {
    Serial.println("RED is HIGH" );
    set_red_led();
  }
  if (request.indexOf("/GREEN=ON") != -1)  {
    Serial.println("GREEN is HIGH" );
    set_green_led();
    
  }
  if (request.indexOf("/BLUE=ON") != -1)  {
    Serial.println("BLUE is HIGH" );
    set_blue_led();   
  }
  if (request.indexOf("/TURNOFF=OFF") != -1)  {
    Serial.println("LED is LOW" );
    turn_off_led();
  }
  
  get_temperature();
  client.print("<strong>~~~ Temperature Sensor ~~~ </strong><br>");
  client.print("Temperature: "); client.println(temperature);
  client.print("<br>Humidity: "); client.println(humidity);

  get_led_status();
  client.print("<br><br><strong>~~~ Led Status ~~~ </strong><br>");
  client.println("RED: "); client.println(redStatus);
  client.print("GREEN: "); client.println(greenStatus);
  client.print("BLUE: "); client.println(blueStatus);

  client.println("<br><br>");
  client.println("<a href=\"/RED=ON\"\"><button>RED ON</button></a>");
  client.println("<a href=\"/GREEN=ON\"\"><button>GREEN ON</button></a>");
  client.println("<a href=\"/BLUE=ON\"\"><button>BLUE ON</button></a>");
  client.println("<a href=\"/TURNOFF=OFF\"\"><button>TURN OFF</button></a>");
  client.println("</html>");
  delay(1);
}
