import gohai.glvideo.*;
import processing.io.*;
GLCapture video;

#define driveComplete 12
#define orange_kitchen 21
#define green_refill 26
#define pink_BTN3 19


color pink   =  color(134,11,63);
color orange =  color(146,41,21);//-7986170;
color green  =  color(18,75,0);//-14987008;
//color blue =  color(21,40,60);//-10136830;


color trackColor[] = {pink,orange,green}; 
float threshold = 25;
float distThreshold = 50;

int colorDetected[] = {0,0,0};

ArrayList<Blob> blobs = new ArrayList<Blob>();

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

void draw() {
  background(0);
  //////////////////////
  // If the camera is sending new data, capture that data
  if (GPIO.digitalRead(driveComplete, GPIO.LOW){
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
    else {
      // if Arduino makes input pin high, turn on screen and don't use computer vision
      class Button{
        int position[] = {width/2,height/2};//default
        int size[] = {100,75};
        color buttonColor = color(255,0,0);
        color pressedButtonColor = color(200,0,0);
        String name = "Button";
        int shape = 0; //0:Rect, 1: ellipse
        int pin = 0;
       
       void setPin(int val){
         this.pin = val; 
       }
       
        void setButtonColor(int r, int g, int b){
          this.buttonColor = color(r,g,b);
          this.pressedButtonColor = color(0,0,0);
          
        }
        
        void buttonPressed(int value){
          // check if click is inside height
          float buttonTop = this.position[1] + ((this.size[1])/2);
          float buttonBottom = this.position[1] - ((this.size[1])/2);
          float buttonLeft = this.position[0] - ((this.size[0])/2);
          float buttonRight = this.position[0] + ((this.size[0])/2);
          if (mousePressed && (buttonBottom < mouseY) && (mouseY < buttonTop) && (buttonRight > mouseX) && (mouseX > buttonLeft)) {
            //print("This is where we write to the GPIO pins\n");
            GPIO.digitalWrite(this.pin, value);
            fill(this.pressedButtonColor);
          } else {
            fill(this.buttonColor);
            GPIO.digitalWrite(this.pin, GPIO.LOW);
          }
        } 
        
        void show(int x, int y, int w, int h){
          this.position[0] = x;
          this.position[1] = y;
          this.size[0] = w;
          this.size[1] = h;
          
          rectMode(CENTER);
          stroke(255);
          strokeWeight(2);
          this.buttonPressed(GPIO.HIGH);
          this.buttonPressed(GPIO.HIGH);
          this.buttonPressed(GPIO.HIGH);
          rect(this.position[0],this.position[1],this.size[0],this.size[1],15);
          text(name, this.position[0],this.position[1]);
        }
        
        
      }
      
      Button kitchenButton;
      Button refillButton;
      Button orderButton;
      
      void setup(){
        size(1000,600);
        surface.setResizable(true);
        
        kitchenButton = new Button();
        refillButton = new Button();
        orderButton = new Button();
        kitchenButton.setPin(orange_kitchen);
        refillButton.setPin(green_refill);
        orderButton.setPin(pink_order);
        
        
        //GPIO pins
        GPIO.pinMode(orange_kitchen, GPIO.OUTPUT);
        GPIO.pinMode(green_refill, GPIO.OUTPUT);
        GPIO.pinMode(pink_order, GPIO.OUTPUT);
      }
      
      void draw(){
        background(255);
        kitchenButton.setButtonColor(51,204,255);
        refillButton.setButtonColor(154,255,51);
        orderButton.setButtonColor(255,204,51);
        kitchenButton.show(width/2, height/2, width/4, height/2);
        refillButton.show((width/2)+((width/4)+60), height/2, width/4, height/2);
        orderButton.show((width/2)-((width/4)+60), height/2, width/4, height/2);
      }
  }

  //for (Blob b : blobs) {
  //  if (b.size() > 500) {
  //    b.show();
  //  }
  //}

  //textAlign(RIGHT);
  //fill(0);
  //text("distance threshold: " + distThreshold, width-10, 25);
  //text("color threshold: " + threshold, width-10, 50);
   /////////////////////
}

float distSq(float x1, float y1, float x2, float y2) {
  float d = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
  return d;
}


float distSq(float x1, float y1, float z1, float x2, float y2, float z2) {
  float d = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) +(z2-z1)*(z2-z1);
  return d;
}


void mousePressed() {
  // Save color where the mouse is clicked in trackColor variable
  //int loc = mouseX + mouseY*video.width;
  //color trackColor123 = video.pixels[loc];
  
  //print(trackColor,"\n");
  //print("Red Value: ", red(trackColor123),"\n");
  //print("Green Value: ", green(trackColor123),"\n");
  //print("Blue Value: ", blue(trackColor123),"\n");
  
  
  //float redGreenRatio = (green(trackColor) + red(trackColor)) / 2;
  
  //if (green(trackColor) > red(trackColor) && red(trackColor) > blue(trackColor))
  //  print("This color is green\n");
  //else if (red(trackColor) > blue(trackColor) && blue(trackColor) > green(trackColor))
  //  print("This color is pink\n");
  //else if (red(trackColor) > green(trackColor) && green(trackColor) > blue(trackColor) && redGreenRatio > 65)
  //  print("This color is orange\n");
  //else if (red(trackColor) > green(trackColor) && green(trackColor) > blue(trackColor) && redGreenRatio < 65)
  //  print("This color is yellow\n");
}
