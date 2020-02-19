# Alexa Controlled Smart Home System

This projects aims to provide a step by step guidance on building an alexa voice controlled smart home system using nodemcu and few sensors.

This project explores the key IoT platform aspects like device registry, 
device shadows (aka device twins) provided by AWS IoT service to enable communication between hardware boards, sensors and a custom Amazon Alexa skill giving the ability to execute actions via voice commands.

This project aims to guide and enable participants to implement other ideas as well since the blocks/services/concepts used here are very much needed for developing any IoT application.

<a href="https://raw.githubusercontent.com/erviveksoni/alexa-controlled-smart-home-lab/master/images/IOTTeaser.MOV"><img src="https://raw.githubusercontent.com/erviveksoni/alexa-controlled-smart-home-lab/master/images/project_banner.jpeg" alt="Alexa" width="600" border="10" />
<br/></a>

# Prerequisites
## Hardware
- NodeMCU Board with Micro USB Cable 
- 1 DHT11 Temperature Sensor
- 1 RGD LED
- Few Jumper Wires
- 1 Breadboard
- Amazon Alexa Device (optional)

## Software
- [Arduino IDE](https://www.arduino.cc/en/main/software)
- [USB to UART Bridge Virtual COM Port (VCP) drivers](https://www.silabs.com/documents/public/software/Mac_OSX_VCP_Driver.zip)
  > __Note__: Your machine will require a restart after installing this driver.
- Configure Arduino IDE with NodeMCU Board by setting Arduino->Preferences->Additional Boards Manager URLs to:  https://arduino.esp8266.com/stable/package_esp8266com_index.json
- Download the [Arduino ESP8266 filesystem uploader](https://github.com/esp8266/arduino-esp8266fs-plugin#installation) plugin and follow steps under the installation section
  > __Note__: Ensure you extract this plugin under /Users/[your_user_account]/Documents/Arduino/tools
- IDE (VSCode or IntelliJ Idea)
- Python 3.7.x `brew install python`
- Open SSL `brew install openssl`
- AWS Account. You can create one for free [here](https://aws.amazon.com/free/)
- Amazon Alexa Developer account. You can create one for free [here](https://developer.amazon.com)
- Amazon Alexa Device or Alexa App (get it from app store or google play) installed on your phone.
  > __Note__: Ensure you sign in into the Alexa app from the same email address you used for creating Amazon Alexa Developer account. If you are using Alexa device, then the device should be configured with the same email address.
- Download this Repository on your development machine  
  `git clone https://github.com/erviveksoni/alexa-controlled-smart-home-lab`
- `cd` into the `alexa-controlled-smart-home-lab` directory
- Create a new folder `certs` 


# List of Exercises
1. [Exercise 1](https://github.com/erviveksoni/alexa-controlled-smart-home-lab/tree/master/Exercise1/readme.md) - Blink Onboard LED
2. [Exercise 2](https://github.com/erviveksoni/alexa-controlled-smart-home-lab/tree/master/Exercise2/readme.md) - Basis Sensors with NodeMCU
3. [Exercise 3](https://github.com/erviveksoni/alexa-controlled-smart-home-lab/tree/master/Exercise3/readme.md) - Setting up a Web Server on NodeMCU
4. [Exercise 4](https://github.com/erviveksoni/alexa-controlled-smart-home-lab/tree/master/Exercise4/readme.md) - Setting AWS IoT
5. [Exercise 5](https://github.com/erviveksoni/alexa-controlled-smart-home-lab/tree/master/Exercise5/readme.md) - Connecting NodeMCU with AWS IoT
6. [Exercise 6](https://github.com/erviveksoni/alexa-controlled-smart-home-lab/tree/master/Exercise6/readme.md) - Creating Alexa Skill
7. [Exercise 7](https://github.com/erviveksoni/alexa-controlled-smart-home-lab/tree/master/Exercise7/readme.md) - Creating an AWS Lambda Function Endpoint
8. [Exercise 8](https://github.com/erviveksoni/alexa-controlled-smart-home-lab/tree/master/Exercise8/readme.md) - Connecting Alexa Skill to AWS IoT
