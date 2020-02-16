#include "Central.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(getDriveStoppedPin,INPUT); //from Drive
  pinMode(getPinkOrBtn1Pin,INPUT); //from PI
  pinMode(getGreenOrBtn2Pin,INPUT); //from PI
  pinMode(getOrangeOrBtn3Pin,INPUT); //from PI
  
  pinMode(echoRightPin,INPUT); //from Ultrasonic
  pinMode(echoFrontPin,INPUT); //from Ultrasonic
  
 
  pinMode(sendDriveStopPin,OUTPUT); //to Drive
  pinMode(sendDirectionPin,OUTPUT); //to Drive
  pinMode(sendWallAdjustmentPin,OUTPUT); //to Drive
  pinMode(sendDonePin,OUTPUT); //to PI
  
  
  pinMode(triggerRightPin,OUTPUT); //to Ultrasonic
  pinMode(triggerFrontPin,OUTPUT); //to Ultrasonic
}

void loop() {
  // put your main code here, to run repeatedly:

}
