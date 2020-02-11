# Exercise 7 - Creating an AWS Lambda Function Endpoint

Next step is to create an AWS Lambda function which will be invoked by the Alexa skill and will act as a bridge between Skill and AWS IoT. 
The message passed by the Alexa invocation to the Lambda function will be validated against a list of allowed actions and further sent to the Thing we created in the above step.

Every message passed to the Lambda function represents a type of action the user wants to execute. Further every action has a designated MQTT topic defined in the policy attached to the Thing.

#### Creating Lambda Function
- In the AWS developer console, search for `lambda`
- Click `Lambda` in the results to navigate to the Lambda console
- Click `Create function` in the top right corner of the screen
- Put the function name as `Alexafunction`
- Runs time as `Python 3.7`
- Click `Create function`
- In the `Designer` section, click `Add trigger`
- In the Trigger configuration page, select `Alexa Skill Kit`
- Select `disable` option for the Skill ID verification
- Click `Add` to complete adding an alexa trigger
- On the Designer section, click the lambda function icon
- Go to `Basic settings` section of the page
- On a safer side, set memory as `256 MB` and Timeout as `10 seconds`
- Click `Save` button on the top right corner to save changes
- Make a note of the lambda function `ARN` from the top right corner of the screen

#### Packaging Lambda Function Code
- Copy the `certs` folder in the root of the `alexa-controlled-smart-home-lab` directory to the `lambda_function` subdirectory
- `cd` into the `Exercise7/lambda_function` sub directory
- Open `lambda_function.py` file in your preferred text editor 
- Update the config section at the top of this file with the cert names and Rest API Endpoint details you noted earlier 
Also, replace the `<THING_NAME>` with the Thing you created in previous exercise
````python
config = { 
         'host': '<REST API Endpoint>',
         'rootCAName': '<Root certificate file name>',
         'certificateName': '<Certificate file name>',
         'privateKeyName' : '<Private key file name>',
         'clientId': 'alexa_client_lambda',
         'port' : 8883
}

thing_name = "<THING_NAME>"
````
- Save changes and close the file
- Open command line and type
`pip3 install AWSIoTPythonSDK -t .` to download AWSIoTPythonSDK inside the `lambda_function` directory
- Create a zip package with only the **contents** of the `lambda_function` directory

    `zip -9r lambda.zip AWSIoTPythonSDK* certs/* iot_client.py lambda_function.py alexa_response_builder.py`
- At this point you should have a zip file `lambda.zip` ready to be uploaded to AWS Lambda function

#### Upload Lambda Function Package
- Back on the Lambda function console, from the Designer section, click the lamda function icon
- Expand the `Code entry type` dropdown and select `Upload a .zip file`
- Click `Upload` button and browse and select the `lambda.zip` file
- Click `Save` button on the top right corner to save changes

You should now be able to see your code in the online code editor interface of AWS Lambda.
