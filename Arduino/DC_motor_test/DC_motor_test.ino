#include <AFMotor.h>


AF_DCMotor motorLF(1);
AF_DCMotor motorLB(2);
AF_DCMotor motorRB(3);
AF_DCMotor motorRF(4);

//int motorSpeed = 100;
void setup() {
  // put your setup code here, to run once:
  //motorLF.setSpeed(motorSpeed);
  //motorLF.run(RELEASE);
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

void rightTurn(int t, int Speed){

  motorSpeed(Speed);
  motorLF.run(FORWARD);
  motorRF.run(BACKWARD);
  motorLB.run(FORWARD);
  motorRB.run(BACKWARD);

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

void leftTurn(int t, int Speed){

  motorSpeed(Speed);
  motorLF.run(BACKWARD);
  motorRF.run(FORWARD);
  motorLB.run(BACKWARD);
  motorRB.run(FORWARD);
  
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
  right(380, 250);
  delay(1000);
  

  /*
  backward(1000,70);
  right(1000,70);
  left(1000,70);
  diagonalRightBack(1000,70);
  diagonalLeftFront(1000,70);
  diagonalLeftBack(1000,70);
  diagonalRightFront(1000,70);
  turnAround(1000,70);
  turnAround(1000,70);
  */
}
