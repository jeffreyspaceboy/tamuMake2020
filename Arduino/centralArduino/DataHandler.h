
#define getDriveStoppedPin 3 //from Drive
#define getPinkOrBtn1Pin 4 //from PI
#define getGreenOrBtn2Pin 5 //from PI
#define getOrangeOrBtn3Pin 6 //from PI

#define sendDriveStopPin 7 //to Drive
#define sendDirectionPin A1 //to Drive
#define sendWallAdjustmentPin A2 //to Drive
#define sendDonePin 8 //to PI

class DataHandler{
    //Drive
    bool getDriveIsStopped();
    void sendDriveStop(bool shouldStop);
    void sendDirection(int val);
    void sendWallAdjustment(int val);

    //PI
    bool getPinkOrBtn1();
    bool getGreenOrBtn2();
    bool getOrangeOrBtn3();
    void sendDone(bool amDone);
};




//Drive
bool DataHandler::getDriveIsStopped(){
   return digitalRead(getDriveStoppedPin);
}
void DataHandler::sendDriveStop(bool shouldStop){
  if(shouldStop){
    digitalWrite(sendDriveStopPin,HIGH);
  } else {
    digitalWrite(sendDriveStopPin,LOW);
  }
}
void DataHandler::sendDirection(int val){ //0=fwd 1=reverse
  if(val==0){
    analogWrite(sendDirectionPin,255);
  } else{
    analogWrite(sendDirectionPin,0);
  }
}
void DataHandler::sendWallAdjustment(int val){ //2=towardsWall, 1=awayWall, 0=straight 
  if(val==2){
    analogWrite(sendDirectionPin,255);
  } else if(val==1){
    analogWrite(sendDirectionPin,128);
  } else{
    analogWrite(sendDirectionPin,0);
  }
}

//PI
bool DataHandler::getPinkOrBtn1(){
  return digitalRead(getPinkOrBtn1Pin);
}
bool DataHandler::getGreenOrBtn2(){
  return digitalRead(getGreenOrBtn2Pin);
}
bool DataHandler::getOrangeOrBtn3(){
  return digitalRead(getOrangeOrBtn3Pin);
}
void DataHandler::sendDone(bool amDone){
  if(amDone){
    digitalWrite(sendDonePin,HIGH);
  } else {
    digitalWrite(sendDonePin,LOW);
  }
}
