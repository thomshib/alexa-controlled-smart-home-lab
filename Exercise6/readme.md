# Exercise 6 - Creating Alexa Skill

### Creating Alexa Skill
Now we are all set to create an Alexa skill which will interact with user to receive commands.

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
- Click `Build Model` button at the top of the page and wait for the skill build process to complete


### Evaluate the Model

Now as the basic structure for the skill is ready, let's test the utterances to see how they resolve to intents and slots. 

- On the top navigation bar, click `Evaluae Model` button on the right side
- In the text box type `ask my smarthome temperature` and check if this resolves to the `temperatureIntent`	
- Repeat the same to test other intents. All the utterances should resolved to desired intents
