int circleX1, circleY1;      // Position of circle button 1
int circleX2, circleY2;  // Position of circle button 2
int circleX3, circleY3;      // Position of circle button 3
//int circleX4, circleY4;  // Position of circle button 4
int circleSize = 93;   // Diameter of circle
color circleColor1, circleColor2, circleColor3;//, circleColor4;
color currentColor;
boolean circle1Over = false;
boolean circle2Over = false;
boolean circle3Over = false;
//boolean circle4Over = false;
void setup() {
  size(640, 360);
  frameRate(2);
  frame.setResizable(true);
  circleColor1 = color(51,204,255);
  circleColor2 = color(154,255,51);
  circleColor3 = color(255,204,51);
  circleX1 = width/2-circleSize/2-110;
  circleY1 = height/2;
  circleX2 = width/2-circleSize/2-10;
  circleY2 = height/2;
  circleX3 = width/2+circleSize/2;
  circleY3 = height/2;
  ellipseMode(CENTER);
}

void draw() {
  update(mouseX, mouseY);
  background(255);
  
  if (circle1Over) {
    fill(1,154,255);
  } else {
    fill(circleColor1);
  }
  stroke(0);
  ellipse(circleX1, circleY1, circleSize, circleSize);
  textSize(14);
  fill(0);
  text("Order",circleX1-16, circleY1+5);
  
  if (circle2Over){
    fill(97,255,0);
  }
  else{
    fill(circleColor2);
  }
  stroke(0);
  ellipse(circleX2, circleY2, circleSize, circleSize);
  textSize(14);
  fill(0);
  text("To Kitchen",circleX2-33, circleY2+5);
  if (circle3Over){
    fill(255,154,1);
  }
  else{
    fill(circleColor3);
  }
  stroke(0);
  ellipse(circleX3, circleY3, circleSize, circleSize);
  textSize(14);
  fill(0);
  text("To Table",circleX3-25, circleY3+5);
  /*if (circle4Over){
    fill(97,255,0);
  }
  else{
    fill(circleColor4);
  }
  stroke(0);
  ellipse(circleX4, circleY4, circleSize, circleSize);
  textSize(14);
  fill(0);
  text("",circleX4-33, circleY4+5);*/
}

void update(int x, int y) {
  if ( overCircle(circleX1, circleY1, circleSize) ) {
    circle1Over = true;
    circle2Over = false;
    circle3Over = false;
    //circle4Over = false;
  }
  else if( overCircle(circleX2, circleY2, circleSize)){
    circle1Over = false;
    circle2Over = true;
    circle3Over = false;
    //circle4Over = false;
  }
  else if( overCircle(circleX3, circleY3, circleSize)){
    circle1Over = false;
    circle2Over = false;
    circle3Over = true;
    //circle4Over = false;
  }
 /*else if( overCircle(circleX4, circleY4, circleSize)){
    circle1Over = false;
    circle2Over = false;
    circle3Over = false;
    circle4Over = true;
  }*/
  else{
    circle1Over = circle2Over = circle3Over /*=circle4Over*/ = false;
  }
}

void mousePressed() {
  if (circle1Over == true) {
    currentColor = circleColor1;
  }
  else if (circle2Over ==true){
    currentColor = circleColor2;
  }
  else if (circle3Over ==true){
    currentColor = circleColor3;
  }
  /*else if (circle4Over ==true){
    currentColor = circleColor4;
  }*/
  else{
    return;
  }
}

boolean overCircle(int x, int y, int diameter) {
  float disX = x - mouseX;
  float disY = y - mouseY;
  if (sqrt(sq(disX) + sq(disY)) < diameter/2 ) {
    return true;
  } else {
    return false;
  }
}
