#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED_PIN 5
#define LED_COUNT 50

#define DELAYVAL 500

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int half = 0;
bool group = false;
void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  pixels.show();
  pixels.setBrightness(100);

  
}

void colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for(uint16_t i=0; i<LED_COUNT; i++) {
      pixels.setPixelColor(i, red, green, blue);
      pixels.show();
      delay(SpeedDelay);
  }
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< LED_COUNT; i++) {
      c=Wheel(((i * 256 / LED_COUNT) + j) & 255);
      pixels.setPixelColor(i, *c, *(c+1), *(c+2));
    }
    pixels.show();
    delay(SpeedDelay);
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
 
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}


void greenflashing(){
  //green case
    if (half % 2 == 0){
      for (int i = 0; i<LED_COUNT; i = i+2){
      pixels.setPixelColor(i, pixels.Color(252, 82, 3));  // green, red, blue
      }
    }else{
      for (int i = 1; i<LED_COUNT; i = i+2){
      pixels.setPixelColor(i, pixels.Color(252, 82, 3));
      }
    }
    pixels.show();
    half = half +1;
}

void flashing(){
  if (group == false){
    if (half % 2 == 0){
      for (int i = 0; i<LED_COUNT; i = i+2){
      pixels.setPixelColor(i, pixels.Color(252, 82, 3));
      pixels.setPixelColor(i+1, pixels.Color(194, 3, 252));
      }
      
    }else{
      for (int i = 1; i<LED_COUNT; i = i+2){
      pixels.setPixelColor(i, pixels.Color(252, 82, 3));
      pixels.setPixelColor(i-1, pixels.Color(194, 3, 252));
      }
    }
    pixels.show();
    delay(DELAYVAL);
    half = half +1;
    if (half % 2 == 0){
      group = !group;
    }

  } else{
      if (half % 2 == 0){
      for (int i = 0; i<LED_COUNT; i = i+2){
      pixels.setPixelColor(i, pixels.Color(173, 252, 3));
      pixels.setPixelColor(i+1, pixels.Color(3, 252, 107));
      }
      
    }else{
      for (int i = 1; i<LED_COUNT; i = i+2){
      pixels.setPixelColor(i, pixels.Color(173, 252, 3));
      pixels.setPixelColor(i-1, pixels.Color(3, 252, 107));
      }
    }
    pixels.show();
    delay(DELAYVAL);
    half = half +1;
    if (half % 2 == 0){
      group = !group;
    }
    }
}



void loop() {
  // put your main code here, to run repeatedly:
  //pixels.clear();
    //flashing();
    //greenflashing();
    //TheaterChaseUpdate();
    //rainbowCycle(20);
    //colorWipe(0,255,0, 30);
    //colorWipe(0,0,255, 30);
  //for(int i=0; i<LED_COUNT; i++) {

//    pixels.setPixelColor(5, pixels.Color(150, 0, 0));
//    pixels.setPixelColor(25, pixels.Color(0, 0, 150));
    //pixels.show();
    //delay(DELAYVAL);
  //}

}
