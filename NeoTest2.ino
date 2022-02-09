//CODE INSPIRED BY ADAFRUIT EXAMPLE BUTTONCYCLER
//USING BUTTON TO ITERATE THROUGH 4 MODE 0-3. OFF, RED, GREEN, BLUE
//use the library manager to install the library first
//include the library
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Digital IO pin connected to the button. This will be driven with a
// pull-up resistor so the switch pulls the pin to ground momentarily.
// On a high -> low transition the button press logic will execute.
#define BUTTON_PIN 5 //Button designation

#define PIXEL_PIN 6  // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 4  // Number of NeoPixels

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags

boolean oldState = HIGH; //Button State designation
int     mode     = 0;    // Currently-active animation mode, 0-3

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'
}

void loop() {
 
  boolean newState = digitalRead(BUTTON_PIN);//Current button state

  // Check if state changed from high to low (button press).
 if((newState == LOW) && (oldState == HIGH)) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if(newState == LOW) {      // Yes, still low
      if(++mode > 3) mode = 0; // Advance to next mode, wrap around after #3
      switch(mode) {           // Start the new animation...
        case 0:
          colorWipe(strip.Color(  0,   0,   255), 50);    //BLUE
          break;
        case 1:
          colorWipe(strip.Color(0,   0,   0), 50);    // OFF
          break;
        case 2:
          colorWipe(strip.Color(  255, 0,   0), 50);    // RED
          break;
        case 3:
          colorWipe(strip.Color(  0,   255, 0), 50);    // GREEN
          break;
      }
    }
  }

  // Set the last-read button state to the old state.
  oldState = newState;
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color 
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
















  
