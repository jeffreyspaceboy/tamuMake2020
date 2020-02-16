#include <AFMotor.h>


AF_DCMotor motorLF(1);  //motor setup
AF_DCMotor motorLB(2);
AF_DCMotor motorRB(3);
AF_DCMotor motorRF(4);

#define trigPin A5
#define echoPin A4

#define highSpeed 150
#define lowSpeed 100

#define wallDist

void motorStop(){
  motorLF.run(RELEASE);
  motorRF.run(RELEASE);
  motorLB.run(RELEASE);
  motorRB.run(RELEASE);
}

void motorForward(){
  motorLF.run(FORWARD);
  motorRF.run(FORWARD);
  motorLB.run(FORWARD);
  motorRB.run(FORWARD);
}


void towardsWall()
{
  motorForward();
  motorLF.setSpeed(highSpeed);
  motorLB.setSpeed(highSpeed);
  motorRF.setSpeed(lowSpeed);
  motorRB.setSpeed(lowSpeed);
  
}

void awayWall()
{
  motorForward();
  motorLF.setSpeed(lowSpeed);
  motorLB.setSpeed(lowSpeed);
  motorRF.setSpeed(highSpeed+50);
  motorRB.setSpeed(highSpeed+50);
}

void straight()
{
  motorForward();
  motorRF.setSpeed(highSpeed);
  motorRB.setSpeed(highSpeed);
  motorLF.setSpeed(highSpeed);
  motorLB.setSpeed(highSpeed);
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  pinMode(echoPin, INPUT);
  double duration = pulseIn(echoPin, HIGH);
  double cm = (duration/2) / 29.1;
  Serial.println(cm);
  if (cm > 20) {
    towardsWall();
    //Serial.println("Move towards wall");
  } else if (cm < 20) {
    //motorStop();
    awayWall();
    //Serial.println("Move away from wall");
  } else {
    //motorStop();
    straight();
    //Serial.println("Straight");
  }
  delay(100);
  motorStop();
  delay(100);
}
