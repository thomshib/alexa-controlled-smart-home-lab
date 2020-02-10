##############################
# Responses
##############################


def conversation(title, body, session_attributes):
    speechlet = {}
    speechlet['outputSpeech'] = build_PlainSpeech(body)
    speechlet['card'] = build_SimpleCard_image(body)
    speechlet['shouldEndSession'] = False
    return build_response(speechlet, session_attributes=session_attributes)


def simple_statement(body):
    speechlet = {}
    speechlet['outputSpeech'] = build_PlainSpeech(body)
    speechlet['card'] = build_SimpleCard(body)
    speechlet['shouldEndSession'] = True
    return build_response(speechlet)


def statement(body):
    speechlet = {}
    speechlet['outputSpeech'] = build_PlainSpeech(body)
    speechlet['card'] = build_SimpleCard_image(body)
    speechlet['shouldEndSession'] = True
    return build_response(speechlet)


def continue_dialog():
    message = {}
    message['shouldEndSession'] = False
    message['card'] = build_SimpleCard_image(None)
    message['directives'] = [{'type': 'Dialog.Delegate'}]
    return build_response(message)


def build_PlainSpeech(body):
    speech = {}
    speech['type'] = 'PlainText'
    speech['text'] = body
    return speech


##############################
# Card Builders
##############################

def build_response(message, session_attributes={}):
    response = {}
    response['version'] = '1.0'
    response['sessionAttributes'] = session_attributes
    response['response'] = message
    return response


def build_SimpleCard(body):
    card = {}
    card['type'] = 'Simple'
    card['title'] = 'Home'
    card['content'] = body
    return card


def build_SimpleCard_image(body):
    card = {}
    card['type'] = 'Standard'
    card['title'] = 'Home'
    card['text'] = body
    card['image'] = {}
    card['image'][
        'smallImageUrl'] = 'https://9to5mac.com/wp-content/uploads/sites/6/2019/05/categories-of-smart-home-tech.jpg?quality=82&strip=all'
    card['image'][
        'largeImageUrl'] = 'https://9to5mac.com/wp-content/uploads/sites/6/2019/05/categories-of-smart-home-tech.jpg?quality=82&strip=all'

    return card