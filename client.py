import serial
import json
from websocket import create_connection
import ssl
import time
import pygame

receivedData = create_connection("wss://emotivcortex.com:54321", sslopt={"cert_reqs": ssl.CERT_NONE})
ser = serial.Serial('COM6', 9600)
pygame.init()
pygame.display.set_caption("Mr. Face")
window = pygame.display.set_mode((200, 160))

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

    print(receivedData.recv())

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

    print(receivedData.recv())

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

    print(receivedData.recv())

def get_value():
    data = json.loads(receivedData.recv())
    if 'fac' in data:
        value = data['fac']
        return value
    else:
        return -1

setup()

exit_flag = False
window.fill((0, 0, 0))

while not exit_flag and get_value()!=-1:
    pygame.display.update()
    print(get_value())
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            exit_flag = True

pygame.quit()
