


#include "Motors.h"

MotorGroup::MotorGroup(uint8_t p1, uint8_t p2, uint8_t speedPin) : 
  p1(p1), p2(p2), speedPin(speedPin)
{      
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(speedPin, OUTPUT);
}

    
MotorGroup::~MotorGroup() 
{
}

void MotorGroup::rotate(uint8_t speed, bool clockwise) 
{
  analogWrite(speedPin, speed);
  digitalWrite(p1, (uint8_t)(clockwise ? 1 : 0));
  digitalWrite(p2, (uint8_t)(clockwise ? 0 : 1));
}

Motors::Motors(MotorGroup *leftGrp, MotorGroup *rightGrp, uint8_t standByPin) :
  leftGrp(leftGrp), rightGrp(rightGrp), standByPin(standByPin)
{
  pinMode(standByPin, OUTPUT);
}

Motors::~Motors() 
{
  
}


void Motors::turnLeft() 
{
}

void Motors::turnRight()
{
}

void Motors::moveForward()
{
  rotateAll(true);
}


void Motors::moveBack()
{
  rotateAll(false);
}


void Motors::rotateAll(bool clockwise)
{
  digitalWrite(standByPin, 1); 
  leftGrp->rotate(speed, clockwise);
  rightGrp->rotate(speed, clockwise);
  digitalWrite(standByPin, 0); 
  delay(3000);
  digitalWrite(standByPin, 1); 
}

void Motors::setSpeed(uint8_t speed)
{
  this->speed = speed;
}

/*
void writeMotorSpeed(uint8_t speed)
{
  analogWrite(G1_SPEED_PIN,speed);
  analogWrite(G2_SPEED_PIN,speed);
}

void setMotorSpeed(uint8_t speed)
{
  Serial.println(F("Set motor speed"));
  motorSpeed = speed;
  pinMode(G1_SPEED_PIN, OUTPUT);
  analogWrite(G1_SPEED_PIN, 0);

  pinMode(G2_SPEED_PIN, OUTPUT);
  analogWrite(G2_SPEED_PIN, 0);

  delay(500); 
  writeMotorSpeed(speed);
}

void initMotorPins() 
{
  pinMode(G1_P1, OUTPUT);
  pinMode(G1_P2, OUTPUT);
  pinMode(G2_P1, OUTPUT);
  pinMode(G2_P2, OUTPUT);

  pinMode(STDBY_PIN, OUTPUT);
}

void stopMotor() {

  writeMotorSpeed(255);
  digitalWrite(G1_P1, 0);
  digitalWrite(G1_P2, 0);
  digitalWrite(G2_P1, 0);
  digitalWrite(G2_P2, 0);
}

void cw(int pin1, int pin2)
{
  digitalWrite(pin1, 1);
  digitalWrite(pin2, 0);
 
}

void ccw(int pin1, int pin2)
{
  cw(pin2, pin1);
}



void moveForward() {
  Serial.println("moveForward");

  digitalWrite(STDBY_PIN, 1);
  writeMotorSpeed(0);
  cw(G1_P1, G1_P2);
  cw(G2_P1, G2_P2);

  writeMotorSpeed(motorSpeed);
  delay(3000);
  stopMotor();
  digitalWrite(STDBY_PIN, 0);
}

void moveBackward() {
  Serial.println("moveBackward");

  digitalWrite(STDBY_PIN, 1);
  writeMotorSpeed(0);
  ccw(G1_P1, G1_P2);
  ccw(G2_P1, G2_P2);

  writeMotorSpeed(motorSpeed);
  delay(3000);
  stopMotor();
  digitalWrite(STDBY_PIN, 0);
}

void turnLeft() {
  Serial.println("turnLeft");

  digitalWrite(STDBY_PIN, 1);
  
  analogWrite(G1_SPEED_PIN, 250);
  analogWrite(G2_SPEED_PIN, 150);
  
  ccw(G1_P1, G1_P2);
  cw(G2_P1, G2_P2);
  
  
  delay(100);   
  stopMotor();
  digitalWrite(STDBY_PIN, 0);
  
}

void turnRight() {
  Serial.println("turnRight");

  digitalWrite(STDBY_PIN, 1);

  analogWrite(G2_SPEED_PIN, 250);
  analogWrite(G1_SPEED_PIN, 150);

  ccw(G2_P1, G2_P2);
  cw(G1_P1, G1_P2);
  
  delay(100);
  stopMotor();
  digitalWrite(STDBY_PIN, 0);
}

*/
