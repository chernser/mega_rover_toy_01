

#ifndef _MOTORS_H 
#define _MOTORS_H

//#include <avr/interrupt.h>
//#include <avr/pgmspace.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

class MotorGroup {

  public:
    MotorGroup(uint8_t p1, uint8_t p2, uint8_t speedPin);   
    virtual ~MotorGroup();

    void rotate(uint8_t speed, bool clockwise);

    uint8_t p1, p2, speedPin;
};

class Motors {

public:
  Motors(MotorGroup *leftGrp, MotorGroup *rightGrp, uint8_t standByPin);
  virtual ~Motors();

  void turnLeft();
  void turnRight();
  void moveForward();
  void moveBack();

  void setSpeed(uint8_t speed);

private:

  void rotateAll(bool clockwise);

  MotorGroup *leftGrp;
  MotorGroup *rightGrp;
  uint8_t standByPin;

  uint8_t speed;
};

#endif;
