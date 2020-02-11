# Exercise 6 - Creating Alexa Skill

### Creating Alexa Skill
Now we are all set to create an Alexa skill which will interact with user to receive commands and execute them.

- Sign into [Alexa Skills Kit Developer Console](https://developer.amazon.com/alexa/console/ask) with your credential created in prerequisite section
- Click `Create Skill` button
- Give your skill a name e.g. `My Smarthome`
- Select a default language. Your skill will only appear if the user has this language selected
- Select the model as `Custom` and hosting method as `Provision your own`
- Click `Create skill` button on top right of the screen
- Select the skill template as `Start from scratch` and then click `Choose`
- Click `Invocation` from the left hand navigation
- Specify a Skill Invocation Name e.g. `my smarthome`
- Click `Save Model` button at the top of the page
- Click `JSON Editor` on the left hand navigation
- Copy and paste the contents of the `skill.json` file you downloaded as part of this repository into the editor surface
- Click `Save Model` button at the top of the page
- Feel free to go through the list of intents from the left hand navigation. Every intent represents a command the user can invoke
- Click `Endpoint` from the left hand navigation
~~- Select `AWS Lambda ARN`~~
~~- In the Default Region textbox paste the `ARN` of the Lambda function you noted in the previous section~~
- Click `Save Model` button at the top of the page
~~- Click `Invocation` from the left hand navigation~~
- Click `Build Model` button at the top of the page and wait for the skill build process to complete

#### Test Alexa Skill
Now is the time to put your skill to test!!! 

There are multiple ways to test your skill. The easiest one is by using the Alexa simulator provided in the  Alexa Skills Developer Console
- On the top navigation bar, click `Test`
- Select `Skill testing is enabled in:` as `Development`
- Press the microphone button an speak _`Alexa, open my smarthome`_
- You should receive a voice feedback as _`To start, you should say: Alexa, ask my smarthome to turn on red light.`_
- You can try other commands and alexa should respond back with the command acknowledgement
<br/>

#### Enabling Alexa Skill

- Sign in to https://alexa.amazon.com/ with your Alexa developer account credentials
- Navigate to `Skills` section in the left hand navigation
- Click `Your Skills` on top left of the screen
- Click `Dev Skills` on top navigation
- Click your skill name e.g. `My Smarthome`
- Click `ENABLE` button

This will enable your skill on all devices, iOS and Android apps connected to your Alexa developer account.

Congratulations!! You have successfully created an alexa skill!!
