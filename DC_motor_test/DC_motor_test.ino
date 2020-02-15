#include <AFMotor.h>


AF_DCMotor motorLF(1);
AF_DCMotor motorLB(2);
AF_DCMotor motorRB(3);
AF_DCMotor motorRF(4);

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

  delay(500);
}

void motorSpeed(int Speed){
  motorLF.setSpeed(Speed);
  motorRF.setSpeed(Speed);
  motorLB.setSpeed(Speed);
  motorRB.setSpeed(Speed);
}

void forward(int t, int Speed){

  motorSpeed(Speed);
  motorLF.run(FORWARD);
  motorRF.run(FORWARD);
  motorLB.run(FORWARD);
  motorRB.run(FORWARD);
  
  delay(t);
  motorStop();
}

void right(int t, int Speed){

  motorSpeed(Speed);
  motorLF.run(FORWARD);
  motorRF.run(BACKWARD);
  motorLB.run(BACKWARD);
  motorRB.run(FORWARD);

  delay(t);
  
  motorStop();
}

void diagonalRightFront(int t, int Speed){

  motorSpeed(Speed);
  motorLF.run(FORWARD);
  motorRB.run(FORWARD);

  delay(t);
  
  motorStop();
  
}

void left(int t, int Speed){

  motorSpeed(Speed);
  motorLF.run(BACKWARD);
  motorRF.run(FORWARD);
  motorLB.run(FORWARD);
  motorRB.run(BACKWARD);
  
  delay(t);
  
  motorStop();
}

void diagonalLeftFront(int t, int Speed){

  motorSpeed(Speed);
  motorRF.run(FORWARD);
  motorLB.run(FORWARD);
  
  delay(t);
  
  motorStop();
}

void backward(int t, int Speed){

  motorSpeed(Speed);
  motorLF.run(BACKWARD);
  motorRF.run(BACKWARD);
  motorLB.run(BACKWARD);
  motorRB.run(BACKWARD);
  
  delay(t);
  
  motorStop();
}

void diagonalLeftBack(int t, int Speed){

  motorSpeed(Speed);
  motorLF.run(BACKWARD);
  motorRB.run(BACKWARD);
  
  delay(t);
  
  motorStop();
}

void diagonalRightBack(int t, int Speed){

  motorSpeed(Speed);
  motorRF.run(BACKWARD);
  motorLB.run(BACKWARD);
  
  delay(t);
  
  motorStop();
}

void turnAround(int t, int Speed){

  motorSpeed(Speed);
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
