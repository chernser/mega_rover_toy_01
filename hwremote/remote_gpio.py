from gpiozero import Button
from time import sleep

# From schematic of the HAT 
#   1. 1,2,3 keys are bound to P16, P20, P21 GPIO ports (BCM pin) respectivly 
#   2. joystic's A, B, C, D, Center to P5, P6, P19, P26, P13 (BCM pin) respectivly

key1 = Button(16)
key2 = Button(20)
key3 = Button(21)

# UP  Key pressed <gpiozero.Button object on pin GPIO6, pull_up=True, is_active=True>
# DOWN Key pressed <gpiozero.Button object on pin GPIO19, pull_up=True, is_active=True>
# Left Key pressed <gpiozero.Button object on pin GPIO5, pull_up=True, is_active=True>
# Right Key pressed <gpiozero.Button object on pin GPIO26, pull_up=True, is_active=True>
jA = Button(5)
jB = Button(6)
jC = Button(19)
jD = Button(26)
jCenter = Button(13)

def key_pressed(key):
    print "Key pressed %s" % key

key1.when_pressed = key_pressed    
key2.when_pressed = key_pressed    
key3.when_pressed = key_pressed    

jA.when_pressed = key_pressed    
jB.when_pressed = key_pressed    
jC.when_pressed = key_pressed    
jD.when_pressed = key_pressed    
jCenter.when_pressed = key_pressed    

sleep(20.0)