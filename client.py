mport serial
import json
from websocket import create_connection
import ssl
import time
import os
import sys
import contextlib
from loading_art import upper_img, eye_img, lower_img
with contextlib.redirect_stdout(None):
    import pygame

os.environ["SDL_VIDEO_CENTERED"] = "1"
receivedData = create_connection("wss://emotivcortex.com:54321", sslopt={"cert_reqs": ssl.CERT_NONE})
ser = serial.Serial('COM7', 9600)

def setup():
    receivedData.send(json.dumps({
    "jsonrpc": "2.0",
    "method": "authorize",
    "params": {},
    "id": 1
    }))

    token = receivedData.recv()[43:-3]
    
    receivedData.send(json.dumps({
        "jsonrpc": "2.0",
        "method": "queryHeadsets",
        "params": {},
        "id": 1
    }))

    receivedData.recv()

    receivedData.send(json.dumps({
        "jsonrpc": "2.0",
        "method": "createSession",
        "params": {
            "_auth": token,
            "status": "open",
            "project": "lingua"
        },
        "id": 1
    }))

    receivedData.recv()

    receivedData.send(json.dumps({
        "jsonrpc": "2.0",
        "method": "subscribe",
        "params": {
            "_auth": token,
            "streams": [
                "fac"
            ]
        },
        "id": 1
    }))

    receivedData.recv()

def get_value():
    data = json.loads(receivedData.recv())
    if 'fac' in data:
        value = data['fac']
        return value
    else:
        return -1

setup()

exit_flag = False

val_dict = {
    'neutral': 0,
    'blink': 1,
    'winkL': 2,
    'winkR': 3,
    'suprise': 1,
    'frown': 2,
    'smile': 1,
    'laugh': 1,
   } 

while not exit_flag and get_value()!=-1:
    data = get_value()
    for d in data:
        if d in val_dict:
            ser.write(val_dict[d].encode())
        else:
            ser.write(0.encode())
