#include <ESP8266WiFi.h>

// GPIO Pins
int red = 5;
int green = 4;
int blue = 0;
int redStatus = digitalRead(red);
int greenStatus = digitalRead(green);
int blueStatus = digitalRead(blue);

// Update these with values suitable for your network configuratons.
/**********************/
const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";
/**********************/

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
  Serial.begin(115200);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
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
    redStatus = digitalRead(red);
  }
  if (request.indexOf("/GREEN=ON") != -1)  {
    Serial.println("GREEN is HIGH" );
    set_green_led();
    greenStatus = digitalRead(green);
  }
  if (request.indexOf("/BLUE=ON") != -1)  {
    Serial.println("BLUE is HIGH" );
    set_blue_led();
    blueStatus = digitalRead(blue);
  }
  if (request.indexOf("/TURNOFF=OFF") != -1)  {
    Serial.println("LED is LOW" );
    turn_off_led();
    redStatus = digitalRead(red);
    greenStatus = digitalRead(green);
    blueStatus = digitalRead(blue);
  }

  client.print("~~~ Led Status ~~~ ");
  client.print("RED: "); client.println(redStatus);
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
