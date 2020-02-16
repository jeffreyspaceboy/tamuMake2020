
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
    void sendDriveStop();
    void sendDirection();
    void sendWallAdjustment();
    bool getDriveIsStopped();
    
//    //Ultrasonic
//    double getDistanceRight();
//    double getDistanceFront();

    //PI
    bool getPinkOrBtn1();
    bool getGreenOrBtn2();
    bool getOrangeOrBtn3();
    void sendDone();
};
