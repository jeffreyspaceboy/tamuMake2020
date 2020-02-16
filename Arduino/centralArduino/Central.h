#include "DataHandler.h"

#define echoRightPin A4 //from Ultrasonic
#define triggerRightPin A5 //to Ultrasonic
#define echoFrontPin 11 //from Ultrasonic
#define triggerFrontPin 12 //to Ultrasonic



class Central{
    int mode = 0; //driveFWDWall, driveBWDWall, PassedWallFront, PassedWallBack, AtTable, AtKitchen
    
    bool dirFWD = true; //0=fwd 1=reverse
    //int wallSetting = 0; //2=towardsWall, 1=awayWall, 0=straight 
      
    DataHandler cDH;
    void mainCentral();

    //Ultrasonic
    double getDistanceRight();
    double getDistanceFront();

    void wallDrive(int wallDist);
};

//    //Drive
//    bool getDriveIsStopped();
//    void sendDriveStop(bool shouldStop);
//    void sendDirection(int val);
//    void sendWallAdjustment(int val);
//
//    //PI
//    bool getPinkOrBtn1();
//    bool getGreenOrBtn2();
//    bool getOrangeOrBtn3();
//    void sendDone(bool amDone);


void Central::mainCentral(){
  switch (var) {
    case 1:
      break;
    case 2:
      break:
    case 3:
  }

  //If two colors detected, stop drive, 
        //once plate removed, send signal back to pi

  //
}


void Central::wallDrive(int wallDist){
  double cm = this->getDistanceRight();
  if (cm > wallDist+5 && cm < 100) {
    cDH.sendWallAdjustment(2);
  } else if (cm < wallDist-5) {
    cDH.sendWallAdjustment(1);
  } else if (cm > 100){
    dirFWD = !dirFWD;
    cDH.sendDirection(dirFWD);
  }else {
    cDH.sendWallAdjustment(0);
  }
}


double Central::getDistanceRight(){
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
double Central::getDistanceFront(){
  digitalWrite(triggerFrontPin, LOW);
  delayMicroseconds(5);
  digitalWrite(triggerFrontPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerFrontPin,LOW);
  pinMode(echoFrontPin, INPUT);
  double duration = pulseIn(echoFrontPin, HIGH);
  double cm = (duration/2) / 29.1;
  Serial.println(cm);
  return cm;
}
