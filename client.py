import serial
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
##static_display = ""

##while True:
##    try:
##        port = input("Input port name\n--> COM")
##        static_display += "Input port name\n--> COM"+port+"\n"
##        if not port.isdigit():
##            print("Invalid Serial")
##            static_display += "Invalid Serial\n"
##            continue
##        port = "COM"+port
##        ser = serial.Serial(port, 9600)
##        print("Successfully Connected!")
##        static_display += "Successfully Connected!\n"
##        break
##    except serial.serialutil.SerialException:
##        print(port+" Not Found")
##        static_display += port+" Not Found\n"
##pygame.init()
##pygame.display.set_caption("Mr. Face")
##window = pygame.display.set_mode((220, 180))
##img = pygame.transform.scale(pygame.image.load("imag.jpg"), (220, 180)).convert_alpha()

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
##window.fill((0, 0, 0))
##window.blit(img, (0, 0))

val_dict = {
    'neutral': 0,
    'surprise': 1,
    'frown': 2,
    'smile': 1,
    'laugh': 2,
    'blink': 3,
    'winkR': 2,
    'winkL': 1,
    'lookR': 4,
    'lookL': 5
    }
def_dict = {
    'surprise': 'raised',
    'frown': 'furrowed',
    'winkR': 'right wink',
    'winkL': 'left wink',
    'lookR': 'right look',
    'lookL': 'left look'
    }

index = 0;

while not exit_flag and get_value()!=-1:
##    pygame.display.update()
    data = get_value()
    data1 = data[1]
    data0 = data[0]
    if data[1] in def_dict:
        data1 = def_dict[data[1]]
    if data[0] in def_dict:
        data0 = def_dict[data[0]]
    face = upper_img[val_dict[data[1]]]+" "+"\t\t"+data1+"\n"+eye_img[val_dict[data[0]]]+" \t\t"+data0+"\n"+lower_img[val_dict[data[3]]]+" \t\t\t"+data[3]
    print("\n"*15+face+"\n"*15)

##    for d in data:
##        if str(d).isalpha():
##            ser.write(str(val_dict[d]).encode())
##        else:
##            ser.write(bytes(round(d*10)))
##    for event in pygame.event.get():
##        if event.type == pygame.QUIT:
##            exit_flag = True

##pygame.quit()
