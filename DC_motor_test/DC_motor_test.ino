#include <AFMotor.h>


AF_DCMotor motorLF(1);
AF_DCMotor motorLB(2);

void setup() {
  // put your setup code here, to run once:
  motorLF.setSpeed(100);
  motorLF.run(RELEASE);
}

void forward(){
  motor.run(
}

void right(){
  
}

void loop() {
  // put your main code here, to run repeatedly:
  motorLF.run(FORWARD);
  delay(1000);
  motorLF.run(RELEASE);
  //motor.run(BACKWARD);
  //motor.run(RELEASE);
  delay(1000);
}
