#! bin/python

import random
import time
import json

from paho.mqtt import client as mqtt_client


broker = '192.168.1.33'
port = 1883
topic = "/home/sensors"
# Generate a Client ID with the publish prefix.
client_id = f'publish-{random.randint(0, 1000)}'
# username = 'emqx'
# password = 'public'

def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = mqtt_client.Client(client_id)
    # client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client


def publish(client):
    msg_count = 1
    while True:
        time.sleep(10)
        payload  = {
            "t": random.uniform(25,28),
            "p": random.uniform(100,110),
            "h": random.uniform(20,30),
            "g": random.uniform(125,150)
        }
        jsonPayload = json.dumps(payload)
        result = client.publish(topic, jsonPayload)
        # result: [0, 1]
        status = result[0]
        if status == 0:
            print(f"Send `{payload}` to topic `{topic}`")
        else:
            print(f"Failed to send message to topic {topic}")
        msg_count += 1
        if msg_count > 500:
            break


def run():
    client = connect_mqtt()
    client.loop_start()
    publish(client)
    client.loop_stop()


if __name__ == '__main__':
    run()
