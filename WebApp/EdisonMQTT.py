#!/usr/bin/python

# Copyright (c) 2013 Roger Light <roger@atchoo.org>
#
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the Eclipse Distribution License v1.0
# which accompanies this distribution. 
#
# The Eclipse Distribution License is available at 
#   http://www.eclipse.org/org/documents/edl-v10.php.
#
# Contributors:
#    Roger Light - initial implementation

# This example shows how you can use the MQTT client in a class.

import sys
import serial
import time
import mraa

uart=mraa.Uart(0)
ser = serial.Serial(uart.getDevicePath(), 9600)
# Must given Arduino time to rest.
# Any time less than this does not seem to work...
time.sleep(1.5)

try:
    import paho.mqtt.client as mqtt
except ImportError:
    # This part is only required to run the example from within the examples
    # directory when the module itself is not installed.
    #
    # If you have the module installed, just use "import paho.mqtt.client"
    import os
    import inspect
    cmd_subfolder = os.path.realpath(os.path.abspath(os.path.join(os.path.split(inspect.getfile( inspect.currentframe() ))[0],"../src")))
    if cmd_subfolder not in sys.path:
        sys.path.insert(0, cmd_subfolder)
    import paho.mqtt.client as mqtt

class MyMQTTClass:
    def __init__(self, clientid=None):
        self._mqttc = mqtt.Client(clientid)
        self._mqttc.on_message = self.mqtt_on_message
        self._mqttc.on_connect = self.mqtt_on_connect
        self._mqttc.on_publish = self.mqtt_on_publish
        self._mqttc.on_subscribe = self.mqtt_on_subscribe

    def mqtt_on_connect(self, mqttc, obj, flags, rc):
        print("rc: "+str(rc))

    def mqtt_on_message(self, mqttc, obj, msg):
	output=str(msg.payload)
	print(""+str(output))
	written = ser.write(msg.payload)

    def mqtt_on_publish(self, mqttc, obj, mid):
        output=str(mid)
	print("mid: " +output)


    def mqtt_on_subscribe(self, mqttc, obj, mid, granted_qos):
        print("Subscribed: "+str(mid)+" "+str(granted_qos))

    def mqtt_on_log(self, mqttc, obj, level, string):
        print(string)
	print("test")

    def run(self):
        self._mqttc.connect("iot.eclipse.org", 1883, 60)
        self._mqttc.subscribe("/martingreg", 0)

        rc = 0
        while rc == 0:
            rc = self._mqttc.loop()
        return rc



# If you want to use a specific client id, use
# mqttc = MyMQTTClass("client-id")
# but note that the client id must be unique on the broker. Leaving the client
# id parameter empty will generate a random id for you.
mqttc = MyMQTTClass()
rc = mqttc.run()
print ("intro: " + str(rc))
