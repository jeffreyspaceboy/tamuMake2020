#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED_PIN 5
#define LED_COUNT 50

#define DELAYVAL 500

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  pixels.show();
  pixels.setBrightness(100);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  pixels.clear();

  for(int i=0; i<LED_COUNT; i++) {

    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels.show();
    delay(DELAYVAL);
  }

}
