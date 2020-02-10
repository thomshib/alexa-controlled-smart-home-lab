#include <ESP8266WiFi.h>

int red = 5;
int green = 4;
int blue = 0;
int redStatus = digitalRead(red);
int greenStatus = digitalRead(green);
int blueStatus = digitalRead(blue);
const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
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

  //Start WiFi server
  server.begin();
  Serial.println("Server started!");

  // Print the IP address
  Serial.print("Use this URL to connect: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void Red() {
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  digitalWrite(blue, HIGH);
}
void Green() {
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(blue, HIGH);
}
void Blue() {
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, LOW);
}
void Off() {
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, HIGH);
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
    Red();
    redStatus = digitalRead(red);
    greenStatus = 0;
    blueStatus = 0;
  }
  if (request.indexOf("/GREEN=ON") != -1)  {
    Serial.println("GREEN is HIGH" );
    Green();
    greenStatus = digitalRead(green);
    redStatus = 0;
    blueStatus = 0;
  }
  if (request.indexOf("/BLUE=ON") != -1)  {
    Serial.println("BLUE is HIGH" );
    Blue();
    blueStatus = digitalRead(blue);
    redStatus = 0;
    greenStatus = 0;
  }
  if (request.indexOf("/OFF=OFF") != -1)  {
    Off();
  }

  client.print("Led Status : ");client.println();
  client.print("RED: "); client.println(redStatus);
  client.print("GREEN: "); client.println(greenStatus);
  client.print("BLUE: "); client.println(blueStatus);

  client.println("<br><br>");
  client.println("<a href=\"/RED=ON\"\"><button>RED ON</button></a>");
  client.println("<a href=\"/GREEN=ON\"\"><button>GREEN ON</button></a>");
  client.println("<a href=\"/BLUE=ON\"\"><button>BLUE ON</button></a>");
  client.println("<a href=\"/OFF=OFF\"\"><button>OFF</button></a>");
  client.println("</html>");



  delay(1);

}
