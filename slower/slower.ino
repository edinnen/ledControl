#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

uint16_t hour = 8;
uint16_t minu = 0;
uint16_t sec = 0;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
//  #if defined (__AVR_ATtiny85__)
//    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
//  #endif
  // End of trinket special code

  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(100);  
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  if (hour >= 8 && hour < 19) {
    go();
  } else if (hour >= 19 || hour < 8) {
    setOff();
  }
  delay(1000);
  sec++;
  if (sec == 60) {
    minu++;
    sec = 0;
  }
  if (minu == 60) {
    hour++;
    minu = 0;
  }
  if (hour == 24) {
    hour = 0;
  }

}

void setOff() {
  for (uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
  return;
}

void go() {
  for (uint16_t i=0; i<strip.numPixels(); i++) {
//    if (i%4 == 0) {
//      strip.setPixelColor(i, strip.Color(0,0,255));
//    } else if (i%2 == 0) {
//      strip.setPixelColor(i, strip.Color(131,0,181));
//    } else {
//      strip.setPixelColor(i, strip.Color(255,0,0));
//    }
        strip.setPixelColor(i, strip.Color(255,0,255));
  }
  strip.show();
  return;
}
