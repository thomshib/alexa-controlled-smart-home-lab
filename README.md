# Alexa Controlled Smart Home System

# Prerequisites
## Hardware
- NodeMCU Board with Micro USB Cable 
- 1 DHT11 Temperature Sensor
- 1 RGD LED
- Few Jumper Wires
- 1 Breadboard

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
