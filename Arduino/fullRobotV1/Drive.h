#include <AFMotor.h>

#include "DataHandler.h"



AF_DCMotor motorLF(1);  //motor setup
AF_DCMotor motorLB(2);
AF_DCMotor motorRB(3);
AF_DCMotor motorRF(4);

class Drive{
  private:
    bool isStopped = false;
    bool moveForward = true;
    int highSpeed = 130;
    int lowSpeed = 100;
    DataHandler dDH;
  public:
    void mainDrive();
    void motorStop();
    void motorForward();
    void motorBackward();
    void towardsWall(int leftSpeed, int rightSpeed);
    void awayWall(int leftSpeed, int rightSpeed);
    void straight(int leftSpeed, int rightSpeed);
    void dir();
};

void Drive::mainDrive(){
  if(dDH.readStop()){
    motorStop();
    Serial.print("STOP");
  }else{
    if(dDH.readDirection() == 0){
      moveForward = true;
      Serial.print("MOTOR FWD -");
    }else{
      moveForward = false;
      Serial.print("MOTOR BWD -");
    }

    if(dDH.readWallAdjustment() == 2){ //2=towardsWall, 1=awayWall, 0=straight
      towardsWall(highSpeed-30, lowSpeed);
      Serial.print(" TOWARDS");
    } else if (dDH.readWallAdjustment() == 1) {
      awayWall(lowSpeed, highSpeed+30);
      Serial.print(" AWAY");
    } else {
      straight(highSpeed-40, highSpeed);
      Serial.print(" STRAIGHT");
    }
  }
  Serial.println(" ");
}


void Drive::towardsWall(int leftSpeed, int rightSpeed){
  dir();
  motorLF.setSpeed(leftSpeed);
  motorLB.setSpeed(leftSpeed);
  motorRF.setSpeed(rightSpeed);
  motorRB.setSpeed(rightSpeed);
}

void Drive::awayWall(int leftSpeed, int rightSpeed){
  dir();
  motorLF.setSpeed(leftSpeed);
  motorLB.setSpeed(leftSpeed);
  motorRF.setSpeed(rightSpeed);
  motorRB.setSpeed(rightSpeed);
}

void Drive::straight(int leftSpeed, int rightSpeed){
  dir();
  motorLF.setSpeed(leftSpeed);
  motorLB.setSpeed(leftSpeed);
  motorRF.setSpeed(rightSpeed);
  motorRB.setSpeed(rightSpeed);
}

void Drive::dir(){
  if(moveForward){
    motorForward();
  }else{
    motorBackward();
  }
}

void Drive::motorStop(){
  motorLF.run(RELEASE);
  motorRF.run(RELEASE);
  motorLB.run(RELEASE);
  motorRB.run(RELEASE);
}

void Drive::motorForward(){
  motorLF.run(FORWARD);
  motorRF.run(FORWARD);
  motorLB.run(FORWARD);
  motorRB.run(FORWARD);
}

void Drive::motorBackward(){
  motorLF.run(BACKWARD);
  motorRF.run(BACKWARD);
  motorLB.run(BACKWARD);
  motorRB.run(BACKWARD);
}
