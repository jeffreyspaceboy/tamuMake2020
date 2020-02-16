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
  
  boolean buttonPressed(){
    // check if click is inside height
    float buttonTop = this.position[1] + ((this.size[1])/2);
    float buttonBottom = this.position[1] - ((this.size[1])/2);
    float buttonLeft = this.position[0] - ((this.size[0])/2);
    float buttonRight = this.position[0] + ((this.size[0])/2);
    if (mousePressed && (buttonBottom < mouseY) && (mouseY < buttonTop) && (buttonRight > mouseX) && (mouseX > buttonLeft)) {
      //print("This is where we write to the GPIO pins\n");
      GPIO.digitalWrite(this.pin, GPIO.HIGH);
      fill(this.pressedButtonColor);
      return true;
    } else {
      fill(this.buttonColor);
      GPIO.digitalWrite(this.pin, GPIO.LOW);
      return false;
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
