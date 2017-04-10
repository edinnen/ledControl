 #include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN, NEO_GRB + NEO_KHZ800);

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

  doThing();

  delay(100);

//  buttonState = digitalRead(button);
//
//  if (buttonState == LOW) {
//    setWhite();
//  } else {
//
//    for(uint16_t i=0; i<5; i++) {
//      openClose(10+(i));
//    }
//
//
//    for(uint16_t i=0; i<5; i++) {
//     separate(30-i);
//    }
//
//    for(uint16_t i=0; i<2; i++) {
//      // Some example procedures showing how to display to the pixels:
//      Serial.println("Red wipe");
//      colorWipe(strip.Color(255, 0, 0), 5); // Red
//      chase(25);
//      Serial.println("Green wipe");
//      colorWipe(strip.Color(0, 255, 0), 5); // Green
//      chase(25);
//      Serial.println("Blue wipe");
//      colorWipe(strip.Color(0, 0, 255), 5); // Blue
//      chase(25);
//      ////colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
//    }
//
//    for(uint16_t i=0; i<50; i++) {
//     Serial.println("Random");
//     rando();
//    }
//
//  //  // Send a theater pixel chase in...
//    Serial.println("Theater chase white");
//    theaterChase(strip.Color(127, 127, 127), 10); // White
//    Serial.println("Theater chase red");
//    theaterChase(strip.Color(127, 0, 0), 10); // Red
//    Serial.println("Theater chase blue");
//    theaterChase(strip.Color(0, 0, 127), 10); // Blue
//
//    Serial.println("Rainbow with delay of 20ms");
//    rainbow(20);
//    Serial.println("Rainbow cycle with delay of 20ms");
//    rainbowCycle(20);
//    Serial.println("Theater chase rainbow with delay of 50ms");
//    theaterChaseRainbow(50);
//  }
}

void doThing() {
    for(uint16_t i=0; i<10; i++) {
      growMid(1);
    }

    for(uint16_t i=0; i<10; i++) {
      colorWipe(strip.Color(255, 0, 0));
    }

    for(uint16_t i=0; i<10; i++) {
      colorWipe(strip.Color(0, 255, 0));
    }

    for(uint16_t i=0; i<10; i++) {
      colorWipe(strip.Color(0, 0, 255));
    }

    for(uint16_t i=0; i<15; i++) {
      chase(0,true);
    }
    
    for(uint16_t i=0; i<150; i++) {
      strobe(strip.Color(255,0,0), 50+(i/2));
      strobe(strip.Color(0,255,0), 50+(i/2));
      strobe(strip.Color(0,0,255), 50+(i/2));
    }
   
  }

void setOff() {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
}

void setWhite() {
  uint32_t pixColor = strip.getPixelColor(30);
  if(pixColor == 8092539) {
    return;
  } else {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(127, 127, 127));
    }
    strip.show();
  }
}

void strobe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0); 
  }
  strip.show();
  delay(wait);
}

void growMid(uint8_t wait) {
  uint16_t mid = (strip.numPixels()/2)-1;
  Serial.println(mid);

  for (uint16_t i=mid; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,255));
    strip.setPixelColor(strip.numPixels()-i-1, strip.Color(0,0,255));
    strip.show();
    delay(wait);
  }

  for (uint16_t i=mid; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
    strip.setPixelColor(strip.numPixels()-i-1, 0);
    strip.show();
    delay(wait);
  }
}

void separate(uint8_t wait) {
  uint16_t mid = strip.numPixels()/2;
  //long randNum = random(0,255);
  Serial.println(mid);
  strip.setPixelColor(mid, strip.Color(255,0,0));
  strip.show();
  delay(wait);
  strip.setPixelColor(mid, 0);
  strip.setPixelColor(mid+1, strip.Color(255,0,0));
  strip.setPixelColor(mid-1, strip.Color(0,0,255));
  strip.setPixelColor(mid+2, strip.Color(255,0,0));
  strip.setPixelColor(mid-2, strip.Color(0,0,255));
  strip.setPixelColor(mid+3, strip.Color(255,0,0));
  strip.setPixelColor(mid-3, strip.Color(0,0,255));
  strip.show();
  delay(wait);
  for(uint16_t i=3; i<strip.numPixels()-6; i++) {
    strip.setPixelColor(mid+(i-1), 0);
    strip.setPixelColor(mid-(i-1), 0);
    strip.setPixelColor(mid+(i-2), 0);
    strip.setPixelColor(mid-(i-2), 0);
    strip.setPixelColor(mid+(i-3), 0);
    strip.setPixelColor(mid-(i-3), 0);
    strip.setPixelColor(mid+i, strip.Color(255,0,0));
    strip.setPixelColor(mid-i, strip.Color(0,0,255));
    strip.setPixelColor(mid+(i+1), strip.Color(255,0,0));
    strip.setPixelColor(mid-(i-1), strip.Color(0,0,255));
    strip.setPixelColor(mid+(i+2), strip.Color(255,0,0));
    strip.setPixelColor(mid-(i-2), strip.Color(0,0,255));
    strip.show();
    if(i<strip.numPixels()-7){
      delay(wait);
    }
  }
}

void chase(uint8_t wait, boolean all) {
  for(uint16_t i=0; i<strip.numPixels()+124; i++) {
      strip.setPixelColor(i, Wheel((i * 256 / strip.numPixels())));
      strip.setPixelColor(i-4, 0);
      strip.setPixelColor(i-8, Wheel((i * 256 / strip.numPixels())));
      strip.setPixelColor(i-12, 0);
      strip.setPixelColor(i-16, Wheel((i * 256 / strip.numPixels())));
      strip.setPixelColor(i-20, 0);
      if(all) {
        strip.setPixelColor(i-24, Wheel((i * 256 / strip.numPixels())));
        strip.setPixelColor(i-28, 0);
        strip.setPixelColor(i-32, Wheel((i * 256 / strip.numPixels())));
        strip.setPixelColor(i-36, 0);
        strip.setPixelColor(i-40, Wheel((i * 256 / strip.numPixels())));
        strip.setPixelColor(i-44, 0);
        strip.setPixelColor(i-48, Wheel((i * 256 / strip.numPixels())));
        strip.setPixelColor(i-52, 0);
        strip.setPixelColor(i-56, Wheel((i * 256 / strip.numPixels())));
        strip.setPixelColor(i-60, 0);
        strip.setPixelColor(i-64, Wheel((i * 256 / strip.numPixels())));
        strip.setPixelColor(i-68, 0);
        strip.setPixelColor(i-72, Wheel((i * 256 / strip.numPixels())));
        strip.setPixelColor(i-76, 0);
        strip.setPixelColor(i-80, Wheel((i * 256 / strip.numPixels())));
        strip.setPixelColor(i-84, 0);
        strip.setPixelColor(i-88, Wheel((i * 256 / strip.numPixels())));
        strip.setPixelColor(i-92, 0);
        strip.setPixelColor(i-96, Wheel((i * 256 / strip.numPixels())));
        strip.setPixelColor(i-100, 0);
        strip.setPixelColor(i-104, Wheel((i * 256 / strip.numPixels())));
        strip.setPixelColor(i-108, 0);
        strip.setPixelColor(i-112, Wheel((i * 256 / strip.numPixels())));
        strip.setPixelColor(i-124, 0);
      }
      strip.show();
      if(i<strip.numPixels()+124) {
        delay(wait);
      }
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
    strip.show();
  }
//  for(uint16_t i=strip.numPixels()-1; i>0; i--) {
//    strip.setPixelColor(i, 0);
//    strip.show();
//  }
}

void binaryCount(uint32_t c, uint8_t wait) {
  for (int i=0; i<strip.numPixels(); i++) {
    
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
