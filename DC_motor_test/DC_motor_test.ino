#include <AFMotor.h>


AF_DCMotor motorLF(1);
AF_DCMotor motorLB(2);
AF_DCMotor motorRB(3);
AF_DCMotor motorRF(4);

int t = 1000;
int motorSpeed = 100;
void setup() {
  // put your setup code here, to run once:
  motorLF.setSpeed(motorSpeed);
  motorLF.run(RELEASE);
}

void motorStop(){
  motorLF.run(RELEASE);
  motorRF.run(RELEASE);
  motorLB.run(RELEASE);
  motorRB.run(RELEASE);

  delay(t);
}
void forward(){
  
  motorLF.run(FORWARD);
  motorRF.run(FORWARD);
  motorLB.run(FORWARD);
  motorRB.run(FORWARD);
  
  delay(t);
  motorStop();
}

void right(){
  motorLF.run(FORWARD);
  motorRF.run(BACKWARD);
  motorLB.run(BACKWARD);
  motorRB.run(FORWARD);

  delay(t);
  
  motorStop();
}

void rf(){
  motorLF.run(FORWARD);
  motorRB.run(FORWARD);

  delay(t);
  
  motorStop();
  
}

void left(){
  motorLF.run(BACKWARD);
  motorRF.run(FORWARD);
  motorLB.run(FORWARD);
  motorRB.run(BACKWARD);
  
  delay(t);
  
  motorStop();
}

void lf(){
  motorRF.run(FORWARD);
  motorLB.run(FORWARD);
  
  delay(t);
  
  motorStop();
}

void backward(){
  motorLF.run(BACKWARD);
  motorRF.run(BACKWARD);
  motorLB.run(BACKWARD);
  motorRB.run(BACKWARD);
  
  delay(t);
  
  motorStop();
}

void lb(){
  motorLF.run(BACKWARD);
  motorRB.run(BACKWARD);
  
  delay(t);
  
  motorStop();
}

void rb(){
  motorRF.run(BACKWARD);
  motorLB.run(BACKWARD);
  
  delay(t);
  
  motorStop();
}

void turn(){
  motorLF.run(FORWARD);
  motorRF.run(BACKWARD);
  motorLB.run(FORWARD);
  motorRB.run(BACKWARD);
  
  delay(t);
  
  motorStop();
}


void loop() {
  // put your main code here, to run repeatedly:
  /*
  motorLF.run(FORWARD);
  delay(1000);
  motorLF.run(RELEASE);
  
  //motor.run(BACKWARD);
  //motor.run(RELEASE);
  delay(1000);
  */
}
