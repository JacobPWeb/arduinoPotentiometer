#include <Adafruit_NeoPixel.h>

#define PIN            12 //which pin is controlling your led strip.
#define NUMPIXELS      16 //how many pixels does the strip contain.

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

//potentiometer
int potPin = 0;
int val = 0;

void setup() {
  lightSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(potPin);
  ledColourPot(val);
}

void lightSetup() {
   pixels.begin(); 
   //set LED to max brightness
   pixels.setBrightness(255);
   pixels.show();
}

void ledColourPot(float val) {
  val = val/1023; //get the percentage the potentiometer is turned. Max value is 1023
  //if the percentage is greater or equal to 99% make it white
  if(val >= 0.99){
    setLightBarPot(255, 255, 255);
    return; 
  }
  //check if the value is between 0.99 and 0.66;
  bool isBlue = ((val - 0.66) > 0);
  //check if the value is between 0.66 and 0.33;
  bool isGreen = ((val - 0.33) > 0);
  //check if the value is between 0.33 and 0;
  bool isRed = ((val - 0.33) > -0.33);
  float green;
  float blue;
  float red;
  /**
  *  each if block will work out the percentage of each colour. e.g. percentage of 55% is 33% red and 22% green.
  *  the max value is 33% so 33% will equal 100% of LED brightness.
  **/
  if (isBlue) {
    val = val - 0.66;
    green = 0.33 - val;
    red = 0;
    blue = val;    
  } else if (isGreen) {
    val = val - 0.33;
    red = 0.33 - val;
    green = val;
    blue = 0;
  } else if (isRed) {
    blue = 0;
    green = 0;
    red = val;
  }
  /**
  * work out the percentage that 0.33 is. a value of 0.33 is 100%, so 0.20 is 66%
  **/
  red = red/0.33;
  blue = blue/0.33;
  green = green/0.33;
  /**
  * Turn the LED brightness percentage into an actual value.
  **/
  int redLed = 255*red;
  int greenLed = 255*green;
  int blueLed = 255*blue;
  /**
  * Set the colour
  **/
  setLightBarPot(redLed, greenLed, blueLed);
}
void setLightBarPot(int r, int g, int b) {
  for(int i=0;i<NUMPIXELS;i++){
      //change the order here, if you want the order of colours to change.
      pixels.setPixelColor(i, pixels.Color(b,r,g));
      pixels.show();
    }
}
