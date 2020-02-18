# Exercise 3 - Setting up a Web Server on NodeMCU

In this section we will configure the NodeMCU board as a WIFI client and setup a mini web server to host an HTML page.

The HTML page will allow us to switch on/off the LED's and also to view the room temperature in real time.

## Setting the Wifi Credentials
- Include the ESP8266WiFi WIFI library in the sketch by adding the below code at the top of the file
````c
#include <ESP8266WiFi.h>
````

- Declare the SSID and Password variables at the end of variables section of the sketch
- Replace `<SSID>` and `<PASSWORD>` in the code with your WiFi credentials. 
    > __Note__: We recommend to use mobile hotspot for wifi connection. Also ensure your laptop and NodeMCU board are connected to the same WIFI network.
                                                                         
````c
const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";
````

## Setting up a Local Web Server
- Add the following code after the SSID and Password variable declaration

````c
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
````
- Update the `setup()` function by adding the following code towards the end of the function
````c
   setup_wifi();
   configure_local_web_server();
````

- Replace the `loop()` function with the code below
````c
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
````
- Compile the sketch and ensure there are not errors
- Upload the sketch to the board (set the upload speed as `115200`)
- Open the Serial Monitor, and watch for the output. The NodeMCU board should connect with wifi access point. 
Take a note of the IP Address of the NodeMCU as printed on the screen
- Now browse the above printed IP Address on your laptop to open the web page. 
The web page should display 4 buttons and 2 labels for temperature and humidity
    > __Note__: Esure your laptop and NodeMCU board are connected to the same WIFI network.
