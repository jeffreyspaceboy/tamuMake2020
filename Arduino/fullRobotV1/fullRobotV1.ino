#include "Drive.h"


Drive myDrive;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

  pinMode(echoRightPin,INPUT); //from Ultrasonic
  pinMode(echoFrontPin,INPUT); //from Ultrasonic

  pinMode(triggerRightPin,OUTPUT); //to Ultrasonic
  pinMode(triggerFrontPin,OUTPUT); //to Ultrasonic
}

void loop() {
  // put your main code here, to run repeatedly:
  myDrive.mainDrive();
}
