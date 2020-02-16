#include "DataHandler.h"

#define echoRightPin 9 //from Ultrasonic
#define triggerRightPin 10 //to Ultrasonic
#define echoFrontPin 11 //from Ultrasonic
#define triggerFrontPin 12 //to Ultrasonic

class Central{
//    //Drive
//    void sendDriveStop();
//    void sendDirection();
//    void sendWallAdjustment();
//    bool getDriveIsStopped();  
    
//    //PI
//    bool getPinkOrBtn1();
//    bool getGreenOrBtn2();
//    bool getOrangeOrBtn3();
//    void sendDonePin();

    //Ultrasonic
    double getDistanceRight();
    double getDistanceFront();
};





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
