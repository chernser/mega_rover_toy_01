#ifndef _BLE_REMOTE_H 
#define _BLE_REMOTE_H

#include <avr/interrupt.h>
//#include <avr/pgmspace.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

class BleRemote {


public:
  BleRemote(uint8_t txPin, uint8_t rxPin);
  ~BleRemote() {};

  void init();
  
  uint8_t read8bit();

public: 
SoftwareSerial serial;
};

#endif
