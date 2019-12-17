#include <FastLED.h>
#include <IRremote.h>

// How many leds in your strip?
#define NUM_LEDS 60

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define LED_PIN 5
//#define CLOCK_PIN 13
#define BUTTON_PIN 2
#define REMOTE_PIN A4

IRrecv irrecv(REMOTE_PIN);
decode_results result;

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
      Serial.begin(9600);
      irrecv.enableIRIn();
      // Uncomment/edit one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  	  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
      
      // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);

      // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() { 

  restart:

  int BUTTON_STATE = LOW;
  
  if (irrecv.decode(&result)) {
  
  irrecv.resume();
  float REMOTE = result.value; 
  
  if (REMOTE == 3810010624.00) {

  //TURN ALL LEDS OFF
  for (int i = 0; i <= NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    FastLED.show();
  }
  
  for (int i = 0; i <= NUM_LEDS - 2; i++) {
  
  //TURN LED ON  
  leds[i] = CRGB::Cyan;
  FastLED.show();

  //IS BUTTON PRESSED? IF SO, GO TO BEGINNING OF VOID LOOP
  BUTTON_STATE = digitalRead(BUTTON_PIN);
  if (BUTTON_STATE == HIGH) {
    goto restart;
  }
  
  //TURN LED OFF
  leds[i] = CRGB::Black;
  FastLED.show();
  }
  
  //RED LED ON
  leds[59] = CRGB::Red;
  FastLED.show();

  //IS BUTTON PRESSED? IF SO, GO TO BEGINNING OF VOID LOOP
  BUTTON_STATE = digitalRead(BUTTON_PIN);
  if (BUTTON_STATE == HIGH) {
    goto restart;
  }
  
  //RED LED OFF
  leds[59] = CRGB::Black;
  FastLED.show();

  for (int i = NUM_LEDS-2; i >= 0; i--) {

  //TURN LED ON
  leds[i] = CRGB::Cyan;
  FastLED.show();

  //IS BUTTON PRESSED? IF SO, GO TO BEGINNING OF VOID LOOP
  BUTTON_STATE = digitalRead(BUTTON_PIN);
  if (BUTTON_STATE == HIGH) {
    goto restart;
  }
  
  //TURN LED OFF
  leds[i] = CRGB::Black;
  FastLED.show();
  }
  } else {

  //TURN ALL LEDS OFF
  for (int i = 0; i <= NUM_LEDS; i++)
  leds[i] = CRGB::Black;
  FastLED.show();
  }
  }
  
  delay(500);
  }
