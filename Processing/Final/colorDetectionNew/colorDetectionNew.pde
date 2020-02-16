import gohai.glvideo.*;
import processing.io.*;
GLCapture video;

int driveComplete = 12;
int orange_kitchen = 21;
int green_refill = 26;
int pink_order = 19;
int piMode = 6;


color pink   =  color(134,11,63);
color orange =  color(146,41,21);//-7986170;
color green  =  color(18,75,0);//-14987008;
//color blue =  color(21,40,60);//-10136830;

boolean cameraMode = false;
boolean programStarted = false;

color trackColor[] = {pink,orange,green}; 
float threshold = 25;
float distThreshold = 50;

int colorDetected[] = {0,0,0};

ArrayList<Blob> blobs = new ArrayList<Blob>();

Button thankYouButton;
Button startButton;
Button orderButton;

void setup() {  
  size(320, 240, P2D);
  String[] cameras = GLCapture.list();
  printArray(cameras);
  video = new GLCapture(this, cameras[0]);
  video.start();
  //trackColor = color(255, 0, 0);
  
  //GPIO pins
  GPIO.pinMode(orange_kitchen, GPIO.OUTPUT);
  GPIO.pinMode(green_refill, GPIO.OUTPUT);
  GPIO.pinMode(pink_order, GPIO.OUTPUT);
  GPIO.pinMode(driveComplete, GPIO.INPUT);
  
  
  
  surface.setResizable(true);
        
  thankYouButton = new Button();
  startButton = new Button();
  orderButton = new Button();
  thankYouButton.setPin(orange_kitchen);
  startButton.setPin(green_refill);
  orderButton.setPin(pink_order);
  
  
  //GPIO pins
  GPIO.pinMode(orange_kitchen, GPIO.OUTPUT);
  GPIO.pinMode(green_refill, GPIO.OUTPUT);
  GPIO.pinMode(pink_order, GPIO.OUTPUT);
}

void draw() {
  
  //////////////////////
  // If the camera is sending new data, capture that data
  if(GPIO.digitalRead(driveComplete)==GPIO.HIGH){
    cameraMode = false;
  } else{
    cameraMode = true;
  }
  if (cameraMode && programStarted){ //Checking for colors
    GPIO.digitalWrite(piMode, GPIO.HIGH);
    background(0);
    if (video.available()) {
      video.read();
    }
    // Copy pixels into a PImage object and show on the screen
    video.loadPixels();
    //image(video, 0, 0, width, height);
  
    blobs.clear();
    
     // Begin loop to walk through every pixel
    for (int x = 0; x < video.width; x++ ) {
      for (int y = 0; y < video.height; y++ ) {
        int loc = x + y * video.width;
        // What is current color
        color currentColor = video.pixels[loc];
        float r1 = red(currentColor);
        float g1 = green(currentColor);
        float b1 = blue(currentColor);
        for(int z = 0; z < 3; z++){
          float r2 = red(trackColor[z]);
          float g2 = green(trackColor[z]);
          float b2 = blue(trackColor[z]);
    
          float d = distSq(r1, g1, b1, r2, g2, b2); 
    
          if (d < threshold*threshold) {
    
            boolean found = false;
            for (Blob b : blobs) {
              if (b.isNear(x, y)) {
                b.add(x, y);
                found = true;
                autoColor(z);
                //motorOn();
                break;
              }
            }
    
            if (!found) {
              Blob b = new Blob(x, y);
              blobs.add(b);
            }
          }
        }
      }
    }
  }
  else {
    GPIO.digitalWrite(piMode, GPIO.LOW);
    // if Arduino makes input pin high, turn on screen and don't use computer vision
    background(255);
    thankYouButton.setButtonColor(51,204,255);
    startButton.setButtonColor(154,255,51);//programStarted
    orderButton.setButtonColor(255,204,51);
    thankYouButton.show(width/2, height/2, width/4, height/2);
    startButton.show((width/2)+((width/4)+60), height/2, width/4, height/2);
    if(startButton.buttonPressed()){
      programStarted = true;
    }
    orderButton.show((width/2)-((width/4)+60), height/2, width/4, height/2);
    if(thankYouButton.buttonPressed()){
       GPIO.digitalWrite(piMode, GPIO.HIGH);
       cameraMode = true;
    }
    if(orderButton.buttonPressed()){
      
    }
  }
}   

float distSq(float x1, float y1, float x2, float y2) {
  float d = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
  return d;
}


float distSq(float x1, float y1, float z1, float x2, float y2, float z2) {
  float d = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) +(z2-z1)*(z2-z1);
  return d;
}

void autoColor(int z){
  float redGreenRatio = (green(trackColor[z]) + red(trackColor[z])) / 2;
   
  if (green(trackColor[z]) > red(trackColor[z]) && red(trackColor[z]) > blue(trackColor[z]))
    colorDetected[0] = 1;
  else
    colorDetected[0] = 0;
    //print("This color is green\n");
  if (red(trackColor[z]) > blue(trackColor[z]) && blue(trackColor[z]) > green(trackColor[z]))
    colorDetected[1] = 1;
  else
    colorDetected[1] = 0;
    //print("This color is pink\n");
  if (red(trackColor[z]) > green(trackColor[z]) && green(trackColor[z]) > blue(trackColor[z])) //&& redGreenRatio > 65)
    colorDetected[2] = 1;
  else
    colorDetected[2] = 0;
    //print("This color is orange\n");
  //else if (red(trackColor[z]) > green(trackColor[z]) && green(trackColor[z]) > blue(trackColor[z]) && redGreenRatio < 65)
  //  print("This color is blue\n");
  if (colorDetected[0] == 1) 
    GPIO.digitalWrite(green_refill, GPIO.HIGH);
  else
    GPIO.digitalWrite(green_refill, GPIO.LOW);
    
  if (colorDetected[1] == 1) 
    GPIO.digitalWrite(pink_order, GPIO.HIGH);
  else
    GPIO.digitalWrite(pink_order, GPIO.LOW);
    
  if (colorDetected[2] == 1) 
    GPIO.digitalWrite(orange_kitchen, GPIO.HIGH);
  else
    GPIO.digitalWrite(orange_kitchen, GPIO.LOW);
}

/*
drive, check for colors

see colors = stop (Color combo detected by arduino)
Arduino sends back stop

wait for button press (Order, Thank you, Start)
--Order:
  Go to kitchen
    Remember color
  Wait at kitchen for plate
  Go back to color
--Thank you, return to normal mode





//Button iD - arduino
//Color combo iD - arduino
//Ultrasonics - arduino
  
//Color detect - Pi
//switch interface - Pi
//


*/
