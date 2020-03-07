
#include <SoftwareSerial.h>
//#include <AltSoftSerial.h>

#include "Motors.h"
#include "BleRemote.h"

//BleRemote remote(/* tx */ 12, /* rx */ 13);
/*
 * BLE module is HM-10. Work on 9600 baud rate and has old firmware
 * http://www.martyncurrey.com/hm-10-bluetooth-4ble-modules/
 * Baud rate MUST match, otherwise commands are not read properly. 
 * Use some BLE test application for smart phone to quickly check it.
 * Another alternative is to use Software Serial.
 * Disconnect module before uploading the scatch.
 */
BleRemote remote;


/**
 * Left group should be in reverse to right because motors are 
 * fliped
 */
MotorGroup leftGrp(/* p1 */4, /* p2 */3, /* speed pin */ 5);
MotorGroup rightGrp(/* p1 */8, /* p2 */7, /* speed pin */ 6);
Motors motors(&leftGrp, &rightGrp, /* standby pin*/ 2);

void setup() {

  Serial.begin(9600);
  while(!Serial);

  
  remote.init();


  Serial.println("Hello!");
}

void loop() {

  uint8_t command = remote.read8bit();
  uint8_t arg = 0;
 
  if (command > 0) {
    Serial.print(command, HEX);
    delay(100);
    arg = remote.read8bit();
    Serial.println("->");      
    Serial.println(arg);      
    if (command == 0x01) {        
//        Serial.print("Set speed: ");
        motors.setSpeed(arg);
        Serial.println(arg);      
    } else if (command == 0x02) {

      switch(arg) { 
      case 0x12:
        Serial.println("Move forward");
        motors.moveForward();
        break;
      case 0x06: 
        Serial.println("Move back");
        motors.moveBack();
        break;
      case 0x03: 
        Serial.println("Move right");
        motors.turnRight();
        break;
      case 0x09:
        Serial.println("Move left");
        motors.turnLeft();
        break;
      } 
    } else {
      Serial.print(command, HEX);
      Serial.print(arg, HEX);
    }
  } 
  arg = 0;
  command = 0;
}
