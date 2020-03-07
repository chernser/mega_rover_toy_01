

#include "BleRemote.h"

//BleRemote::BleRemote(uint8_t txPin, uint8_t rxPin) :
//  serial(rxPin, txPin)
//{
//  
//}
BleRemote::BleRemote() 
{
  
}

void BleRemote::init() 
{
//  Serial.begin(9600);  
//  delay(1000);

  Serial.print((char *)"ATAT");
  Serial.print((char *)"AT+NOTI1");
}

uint8_t BleRemote::read8bit()
{
  if (Serial.available() > 0) {
    return (uint8_t)Serial.read();
  }

  return 0;
}
