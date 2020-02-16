#include "Drive.h"


Drive myDrive;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(sendStatePin,OUTPUT);
  pinMode(getStopPin,INPUT);
  pinMode(getDirectionPin,INPUT);
  pinMode(getWallAdjustmentPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  myDrive.mainDrive();
}
