import serial
import json
from websocket import create_connection
import ssl
import time
import os
import sys

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

val_dict = {
    'neutral': 0,
    'blink': 1,
    'winkL': 2,
    'winkR': 3,
    'lookL': 4,
    'lookR': 5,
    'surprise': 1,
    'frown': 2,
    'smile': 1,
    'laugh': 2,
   } 

while True:

    start_time = time.time()
    data = get_value()
    print(data)
    end_time = time.time()
    if data!=-1:
        eyeData = str(val_dict[data[0]])
        uData = str(val_dict[data[1]])
        lData = str(val_dict[data[3]])
        ser.write(eyeData.encode())
        ser.write(uData.encode())
        ser.write(lData.encode())
    time.sleep(1-(end_time-start_time))
        
ser.close()
print('Terminated')
