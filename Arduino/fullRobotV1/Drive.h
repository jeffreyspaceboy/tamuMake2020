#include <AFMotor.h>

#define wallDist

#define echoRightPin A4 //from Ultrasonic
#define triggerRightPin A5 //to Ultrasonic
#define echoFrontPin 11 //from Ultrasonic
#define triggerFrontPin 12 //to Ultrasonic

#define getPinkOrBtn1Pin 52 //from PI
#define getGreenOrBtn2Pin 50 //from PI
#define getOrangeOrBtn3Pin 48 //from PI
#define getPiState 51 //from PI
#define sendRobotState 53 //to PI

AF_DCMotor motorLF(1);  //motor setup
AF_DCMotor motorLB(2);
AF_DCMotor motorRB(3);
AF_DCMotor motorRF(4);

int lookingForColorCode[] = {1,1,0};


bool useColors(){
  if(digitalRead(getPiState) == 1){
    return true;
  } else {
    return false;
  }
}

bool findColorCode(){
  int pink = digitalRead(getPinkOrBtn1Pin);
  int green = digitalRead(getGreenOrBtn2Pin);
  int orange = digitalRead(getOrangeOrBtn3Pin);
  int currentColorCode[] = {pink,green,orange};
  if(currentColorCode == lookingForColorCode){
    return true;
  }else{
    return false;
  }
}

int buttonModeSelect(){
  int order = digitalRead(getPinkOrBtn1Pin);
  int start = digitalRead(getGreenOrBtn2Pin);
  int thankYou = digitalRead(getOrangeOrBtn3Pin);
  if(start == true){
    //digitalWrite(sendRobotState,LOW);
  }else if(order == true){
    //digitalWrite(sendRobotState,LOW);
  }else if(thankYou == true){
    //digitalWrite(sendRobotState,LOW);
  }
}



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
  if(!useColors()){
    motorStop();
    Serial.print("STOP");
  }else{
    if(findColorCode()){
      digitalWrite(sendRobotState,HIGH);
    }else{
      digitalWrite(sendRobotState,LOW);
    }
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



//if pi mode is high 
//use colors
//if low 
//use buttons
