//import processing.io.*;

class Button{
  int position[] = {width/2,height/2};//default
  int size[] = {100,75};
  color buttonColor = color(255,0,0);
  color pressedButtonColor = color(200,0,0);
  String name = "Button";
  int shape = 0; //0:Rect, 1: ellipse
 
  void setButtonColor(int r, int g, int b){
    this.buttonColor = color(r,g,b);
    this.pressedButtonColor = color(0,0,0);
    
  }
  
  void buttonPressed(){
    // check if click is inside height
    float buttonTop = this.position[1] + ((this.size[1])/2);
    float buttonBottom = this.position[1] - ((this.size[1])/2);
    float buttonLeft = this.position[0] - ((this.size[0])/2);
    float buttonRight = this.position[0] + ((this.size[0])/2);
    if (mousePressed && (buttonBottom < mouseY) && (mouseY < buttonTop) && (buttonRight > mouseX) && (mouseX > buttonLeft)) {
      print("This is where we write to the GPIO pins\n");
      fill(this.pressedButtonColor);
    } else {
      fill(this.buttonColor);
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
    this.buttonPressed();
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
  
  
  ////GPIO pins
  //GPIO.pinMode(21, GPIO.OUTPUT);
  //GPIO.pinMode(26, GPIO.OUTPUT);
  //GPIO.pinMode(19, GPIO.OUTPUT);
}

void draw(){
  background(255);
  kitchenButton.setButtonColor(255,0,0);
  refillButton.setButtonColor(0,255,0);
  orderButton.setButtonColor(0,0,255);
  kitchenButton.show(width/2, height/2, width/4, height/2);
  refillButton.show((width/2)+((width/4)+60), height/2, width/4, height/2);
  orderButton.show((width/2)-((width/4)+60), height/2, width/4, height/2);
}
