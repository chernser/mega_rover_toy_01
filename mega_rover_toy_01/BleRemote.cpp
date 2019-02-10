

#include "BleRemote.h"

BleRemote::BleRemote(uint8_t txPin, uint8_t rxPin) :
  serial(rxPin, txPin)
{
  
}

void BleRemote::init() 
{
  serial.begin(9600);  
  delay(1000);

  serial.print((char *)"ATAT");
  serial.print((char *)"AT+NOTI1");
}

uint8_t BleRemote::read8bit()
{
  if (serial.available() > 0) {
    return (uint8_t)serial.read();
  }

  return 0;
}
