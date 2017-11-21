#!/usr/env python

import RPi.GPIO as GPIO
import time

print "executing script"

GPIO.setmode(GPIO.BCM)
GPIO.setup(16, GPIO.OUT)
GPIO.setup(20, GPIO.OUT)
GPIO.setup(21, GPIO.OUT)

print "off"
GPIO.output(16, False)
GPIO.output(20, False)
GPIO.output(21, False)

time.sleep(1)
print "on"
GPIO.output(16, True)
time.sleep(1)
GPIO.output(20, True)
time.sleep(1)
GPIO.output(21, True)
time.sleep(2)
GPIO.output(21, False)
time.sleep(1)
GPIO.output(20, False)
time.sleep(1)
GPIO.output(16, False)

print "off"
GPIO.cleanup()
