# Exercise 5 - Connecting NodeMCU with AWS IoT

## Install the following Arduino Libraries
- NTPClient
- PubSubClient

## Updating NodeMCU Sketch Code
- Open `sensor_pubsub.ino` file in arduino IDE
- Update the config section at the top of this file with the SSID, Password of your WIFI network, Rest API Endpoint details with the AWS endpoint you noted earlier and  
`<THING_NAME>` with the Thing you created in previous exercise
     ````c
     const char *ssid = "<SSID>";
     const char *password = "<PASSWORD>";

     const char *thing_name = "<THING_NAME>";
     const char *AWS_endpoint = "<REST API Endpoint>";