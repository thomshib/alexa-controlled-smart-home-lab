# Exercise 2 - Basis Sensors with NodeMCU
In this section we will setup our NodeMCU to change color of RGB Led and read Temperature sensor data
## Schematics
<img src="https://raw.githubusercontent.com/erviveksoni/alexa-controlled-smart-home-lab/master/images/sketch_bb.jpg" alt="NodeMCU" width="600" border="10" />
<br/>

connect NodeMCU to RGB led and temperature sensoras shown in the schematics. 

## Install Temperature Sensor Library
- Open Arduino IDE
- Go to tools -> Manage Libraries...
- Search for DHT
- Click on Install next to DHT Sensor library by Adafruit

## Setting GPIO 
- Include the DHT library in the sketch by adding the below code at the top of the file
````c
#include <DHT.h>
````

- Define the GPIO pins for led and mentioned below
```c
int red_pin = 5;
int green_pin = 4;
int blue_pin = 0;
```
- Define Temperature sensor on GPIO pin 2
                                                                         
````c
#define DHTTYPE DHT11
#define dht_dpin 2
DHT dht(dht_dpin, DHTTYPE);
````
- Define global variables to store temperature and humidity
```c
float temperature = 0;
float humidity = 0;
```

- Replace the `setup()` function with the code below
```c
void setup() 
{
  dht.begin();
  Serial.begin(115200);
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
}
```

- define the functions to control led

```c
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
```
- Define the function to read temperature sensor data
```c
void get_temperature(){
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
}
```
- Replace the `loop()` function with the code below
````c
void loop() {
  set_blue_led();
  delay(1000);
  set_green_led();
  delay(1000);
  set_red_led();
  delay(1000);
  turn_off_led();
  get_temperature();
  Serial.print("Humidity :" );
  Serial.print(humidity);
  Serial.print(" | Temperature :" );
  Serial.println(temperature);

}
````
- Compile the sketch and ensure there are not errors
- Upload the sketch to the board (set the upload speed as `115200`)
- Open the Serial Monitor, and watch for the output. 
- The serial monitor will display temperature and humidity 
- and led should change color from blue -> green -> red
