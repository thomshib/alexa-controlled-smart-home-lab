
import json
import logging
import time

import alexa_response_builder
from iot_client import awsIoTClient

logger = logging.getLogger()
logger.setLevel(logging.DEBUG)
awsclient = None
telemetry_data = None

##############################
# Configurations
##############################

config = {
        'host': '<REST API Endpoint>',
        'rootCAName': '<Root certificate file name>',
        'certificateName': '<Certificate file name>',
        'privateKeyName' : '<Private key file name>',
        'clientId': 'alexa_client_lambda',
        'port' : 8883
}

thing_name = "<THING_NAME>"


##############################
# Program Entry
##############################

def lambda_handler(event, context):
    global awsclient
    response = None

    try:
        awsclient = awsIoTClient(config)
        time.sleep(100e-3)  # 100ms

        if event['request']['type'] == "LaunchRequest":
            response = on_launch(event, context)

        elif event['request']['type'] == "IntentRequest":
            response = intent_router(event, context)

    except Exception as e:
        logging.error(str(e))
        response = on_processing_error(event, context, e)

    return response


def on_launch(event, context):
    logger.info("launch called")
    return alexa_response_builder.statement("To start, you should say: Alexa, ask control light to turn on.")



def on_processing_error(event, context, exc):
    logging.error(exc)
    return alexa_response_builder.statement("An error occurred while processing your request.")

##############################
# Routing
##############################

def intent_router(event, context):
    intent = event['request']['intent']['name']
    logging.info('Alexa intent: ' + intent)

    # Custom Intents

    if intent == "turnoffIntent":
        logger.info("turn off light")
        return respond_intent("Turning off light", "mysmarthome/turnoff", None)
        
    if intent == "turnonIntent":
        logger.info("turn on light")
        if 'value' in event['request']['intent']['slots']['color']:
            value = event['request']['intent']['slots']['color']['value']
            if value == 'red':
                logger.info("turn on red light")
                return respond_intent("Turning on " + str(value) + " light", "mysmarthome/turnonred", value)
            if value == 'blue':
                logger.info("turn on blue light")
                return respond_intent("Turning on " + str(value) + " light", "mysmarthome/turnonblue", value)
            if value == 'green':
                logger.info("turn on green light")
                return respond_intent("Turning on " + str(value) + " light", "mysmarthome/turnongreen", value)
            else:
                 return alexa_response_builder.statement("Color not supplied!")
        else:
            return alexa_response_builder.statement("Color not supplied!")

    # Required Intents

    if intent == "AMAZON.CancelIntent":
        return cancel_intent()

    if intent == "AMAZON.HelpIntent":
        return help_intent()

    if intent == "AMAZON.StopIntent":
        return stop_intent()

    if intent == "AMAZON.FallbackIntent":
        return fallback_intent()

##############################
# Required Intents
##############################


def cancel_intent():
    return alexa_response_builder.simple_statement(
        "You want to cancel")  # don't use CancelIntent as title it causes code reference error during certification


def help_intent():
    return alexa_response_builder.simple_statement("You want help")  # same here don't use CancelIntent


def stop_intent():
    return alexa_response_builder.simple_statement("You want to stop")  # here also don't use StopIntent


def fallback_intent():
    return alexa_response_builder.simple_statement(
        "Sorry, I do not understand the command.")  # here also don't use FallbackIntent


##############################
# Response
##############################

def respond_intent(command, topic, value):
    message = {'value': value}
    payload = json.dumps(message)
    awsclient.publish_message(topic, payload)
    return alexa_response_builder.statement(command)
