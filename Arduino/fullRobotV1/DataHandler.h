
#define getStopPin A0
#define getDirectionPin A1
#define getWallAdjustmentPin A2
#define sendStatePin A3
//INPUTS:
//stop
//direction/turning?
//wall adjustment

//OUTPUTS:
//Confirm Stopped/Moving


class DataHandler{
  public:
    bool readStop();
    int readDirection();
    int readWallAdjustment();
    void sendState(bool isStopped);
};

bool DataHandler::readStop(){
  return digitalRead(getStopPin);
}

int DataHandler::readDirection(){ //Return: 0=fwd 1=reverse
  int val = analogRead(getDirectionPin); 
  if(val>500){
    return 0;
  }else {
    return 1;
  }
}

int DataHandler::readWallAdjustment(){
  int val = analogRead(getWallAdjustmentPin);
  //2=towardsWall, 1=awayWall, 0=straight
  if(val>600){
    return 2;
  }else if(val<600 && val>300){
    return 1;
  }else{
    return 0;
  }
}

void DataHandler::sendState(bool isStopped){
  if(isStopped){
    digitalWrite(sendStatePin, HIGH);
  }else{
    digitalWrite(sendStatePin, LOW);
  }
}
