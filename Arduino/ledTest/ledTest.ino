#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED_PIN 5
#define LED_COUNT 50

#define DELAYVAL 200

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int half = 0;
bool group = false;
void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  pixels.show();
  pixels.setBrightness(100);

  
}

void greenflashing(){
  //green case
    if (half % 2 == 0){
      for (int i = 0; i<LED_COUNT; i = i+2){
      pixels.setPixelColor(i, pixels.Color(252, 82, 3));
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
  pixels.clear();
    //flashing();
    //greenflashing();
    //chase();
  //for(int i=0; i<LED_COUNT; i++) {

//    pixels.setPixelColor(5, pixels.Color(150, 0, 0));
//    pixels.setPixelColor(25, pixels.Color(0, 0, 150));
//    pixels.show();
    delay(DELAYVAL);
  //}

}
