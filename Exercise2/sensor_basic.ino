#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
 

// GPIO Pins
int red_pin = 5;
int green_pin = 4;
int blue_pin = 0;

//Set Temperature sensor to read from GPIO 2 / D4 
#define DHTTYPE DHT11
#define dht_dpin 2
DHT dht(dht_dpin, DHTTYPE);

int redStatus = digitalRead(red_pin);
int greenStatus = digitalRead(green_pin);
int blueStatus = digitalRead(blue_pin);
float temperature = 0;
float humidity = 0;


void setup() 
{
  dht.begin();
  Serial.begin(115200);
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
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
