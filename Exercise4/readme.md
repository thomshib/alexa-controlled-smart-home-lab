# Exercise 4 - Setting AWS IoT

<img src="https://raw.githubusercontent.com/erviveksoni/alexa-controlled-smart-home-lab/master/images/design.png" alt="Alexa" width="600" height="274" border="10" />
<br/>

### Provision AWS IoT Device

Let's start by setting up a device in AWS IoT service.

#### Creating Policy
- [Sign in](https://console.aws.amazon.com/console/home) into the AWS Console
- In the find service section, search for the service `IoT Core`
- On the left hand navigation, click to expand `Secure` and then select `Policies`
- Click `Create` in the top right corner of the screen
- In the create policy screen, click `Advanced mode`
- Provide a policy name e.g. SmartHomePolicy
- In the below JSON. replace the `<REGION>` with your AWS account region, `<ACCOUNT_NUMBER>` with your AWS [Account Id](https://console.aws.amazon.com/billing/home?#/account) and `<THING_NAME>` with the name of the AWS thing you will create e.g. `SmartHomeDevice`
````json5
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Action": [
        "iot:Publish"
      ],
      "Resource": [
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topic/$aws/things/<THING_NAME>/shadow/update",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topic/$aws/things/<THING_NAME>/shadow/get",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topic/smarthome/lightsoff",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topic/smarthome/redlighton",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topic/smarthome/greenlighton",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topic/smarthome/bluelighton"
      ]
    },
    {
      "Effect": "Allow",
      "Action": [
        "iot:Receive"
      ],
      "Resource": [
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topic/$aws/things/<THING_NAME>/shadow/get/accepted",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topic/$aws/things/<THING_NAME>/shadow/get/rejected",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topic/$aws/things/<THING_NAME>/shadow/update/accepted",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topic/$aws/things/<THING_NAME>/shadow/update/rejected",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topic/smarthome/lightsoff",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topic/smarthome/redlighton",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topic/smarthome/greenlighton",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topic/smarthome/bluelighton"
      ]
    },
    {
      "Effect": "Allow",
      "Action": [
        "iot:Subscribe"
      ],
      "Resource": [
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topicfilter/$aws/things/<THING_NAME>/shadow/get/accepted",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topicfilter/$aws/things/<THING_NAME>/shadow/get/rejected",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topicfilter/$aws/things/<THING_NAME>/shadow/update/accepted",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topicfilter/$aws/things/<THING_NAME>/shadow/update/rejected",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topicfilter/smarthome/lightsoff",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topicfilter/smarthome/redlighton",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topicfilter/smarthome/greenlighton",
        "arn:aws:iot:<REGION>:<ACCOUNT_NUMBER>:topicfilter/smarthome/bluelighton"
      ]
    },
    {
      "Effect": "Allow",
      "Action": [
        "iot:Connect"
      ],
      "Resource": "*"
    }
  ]
}
````
- Paste the policy text into the text box and click `Create`

#### Creating a Thing
- On the left hand navigation, click to expand `Manage` and then select `Thing`
- Click `Create` in the top right corner of the screen
- Click `Create a single thing` button in the next screen
- Provide a name for the things e.g. `SmartHomeDevice`. This should be the same name as used during policy creation
- Click `Next`
- Click `Create certificate` in front of One-click certificate creation (recommended)
- Download all the 3 certificate files for your thing (public, private and certificate) and save them into `certs` folder
- Click `Active` button to activate the root CA for AWS IoT
- Download the root CA certificate for AWS IoT from [here](https://docs.aws.amazon.com/iot/latest/developerguide/server-authentication.html#server-authentication-certs) and save it into `certs` folder
- Click `Attach a policy` button and select the policy `SmartHomePolicy` you created in the above section
- Click `Register thing` to finish Thing creation
- Once the Thing is created, open the thing details and click `Interact` in the left hand navigation
- Make a note of the value of `REST API Endpoint` under the HTTPS section for later use. 
e.g. `xxxxxxxxxxxxxx-ats.iot.us-east-2.amazonaws.com`
We will use this endpoint to interact with the Thing later in the process. 

At this point, we are all set to to communicate with the Thing.
