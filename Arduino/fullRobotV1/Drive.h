#include <AFMotor.h>

#define wallDist

#define echoRightPin A4 //from Ultrasonic
#define triggerRightPin A5 //to Ultrasonic
#define echoFrontPin 11 //from Ultrasonic
#define triggerFrontPin 12 //to Ultrasonic

#define getPinkOrBtn1Pin 4 //from PI
#define getGreenOrBtn2Pin 5 //from PI
#define getOrangeOrBtn3Pin 6 //from PI
#define getPiState 7 //from PI
#define sendRobotState 8 //to PI

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
  public:
    void mainDrive();
    void motorStop();
    void motorForward();
    void motorBackward();
    void towardsWall(int leftSpeed, int rightSpeed);
    void awayWall(int leftSpeed, int rightSpeed);
    void straight(int leftSpeed, int rightSpeed);
    void dir();
    double getDistanceRight();
};

void Drive::mainDrive(){
  if(digitalRead(getPiState)==0){
    motorStop();
    Serial.print("STOP");
  }else{
    double cm = getDistanceRight();
    if(cm > wallDist+5 && cm < 100){
      towardsWall(highSpeed-30, lowSpeed);
      Serial.print(" TOWARDS");
    } else if (cm < wallDist-5) {
      awayWall(lowSpeed, highSpeed+30);
      Serial.print(" AWAY");
    } else if (cm > 100){
      moveForward = !moveForward;
    } else {
      straight(highSpeed-40, highSpeed);
      Serial.print(" STRAIGHT");
    }
    delay(50);
    motorStop();
    delay(25);
  }
  Serial.println(" ");
}


double Drive::getDistanceRight(){
  digitalWrite(triggerRightPin, LOW);
  delayMicroseconds(5);
  digitalWrite(triggerRightPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerRightPin,LOW);
  pinMode(echoRightPin, INPUT);
  double duration = pulseIn(echoRightPin, HIGH);
  double cm = (duration/2) / 29.1;
  Serial.println(cm);
  return cm;
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
