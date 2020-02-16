#include <AFMotor.h>


AF_DCMotor motorLF(1);  //motor setup
AF_DCMotor motorLB(2);
AF_DCMotor motorRB(3);
AF_DCMotor motorRF(4);

class Drive{
  private:
    bool moveForward = true;
    int highSpeed = 130;
    int lowSpeed = 100;
  public:
    Drive();
    void motorStop();
    void motorForward();
    void motorBackward();
    void towardsWall(int leftSpeed, int rightSpeed);
    void awayWall(int leftSpeed, int rightSpeed);
    void straight(int leftSpeed, int rightSpeed);
    void dir();
};

void Drive::towardsWall(int leftSpeed, int rightSpeed){
  dir();
  motorLF.setSpeed(highSpeed-30);
  motorLB.setSpeed(highSpeed-30);
  motorRF.setSpeed(lowSpeed);
  motorRB.setSpeed(lowSpeed);
}

void Drive::awayWall(int leftSpeed, int rightSpeed){
  dir();
  motorLF.setSpeed(lowSpeed);
  motorLB.setSpeed(lowSpeed);
  motorRF.setSpeed(highSpeed+30);
  motorRB.setSpeed(highSpeed+30);
}

void Drive::straight(int leftSpeed, int rightSpeed){
  dir();
  motorRF.setSpeed(highSpeed);
  motorRB.setSpeed(highSpeed);
  motorLF.setSpeed(highSpeed-40);
  motorLB.setSpeed(highSpeed-40);
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
