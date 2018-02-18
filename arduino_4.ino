///// declaration of NeoPixels
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 6
#define numberOfPixels 60
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numberOfPixels, PIN, NEO_GRBW + NEO_KHZ800);

// timer variables
unsigned long currentTime;
unsigned long previousTime = 0;
int pause = 80;
bool flashState = LOW;

int one = 0;

int hand_proximity;
int combination;
int swipe_right, swipe_left;
int swipe;

int presets_r [3] = {255, 0, 100 };
int presets_g [3] =  {100, 100, 255};
int presets_b [3] = {0, 255, 0};
int subset_1_count = 0;

int presets_w [3] = {50, 100, 210};
int subset_2_count = 0;



void setup() {
  
  Serial.begin(9600);
  strip.begin(); // start strip
  strip.show(); // Initialize all pixels to 'off'
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
  
}

void loop() {

  serialEvent();
  
  currentTime = millis();   
  bool pFlashState= flashState; 
  timer(&pause, &flashState, &previousTime);

  if (combination == 2) {
//    stripOff();
    pause = 80;
    digitalWrite(9, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(13, LOW);
    digitalWrite(8, LOW);

//    int r, g, b;
//    r = presets_r[subset_1_count];
//    g = presets_g[subset_1_count];
//    b = presets_b[subset_1_count];

    // do a function with the given color presets below here:
    /// a flash function 

    if (flashState!=pFlashState){
      if (flashState == 1){
        strobe(255,10,10); 
      }
      else if (flashState == 0){
        stripOff();
      }
    }
    
  }

  else if (combination == 3) {
    pause = 80;
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(13, LOW);
    digitalWrite(7, LOW);
    
    if (flashState!=pFlashState){
      if (flashState == 1){
        strobe(10,250,10);  
      }
      else if (flashState == 0){
        stripOff();
      }
    }
   }
    
  else if (combination == 4) {
    pause = 160;
    digitalWrite(9, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(13, LOW);
    digitalWrite(8, LOW);
    if (flashState!=pFlashState){
      if (flashState == 1){
//        strobe(10,10,250); 
        strobeWhite(255);
      }
      else if (flashState == 0){
        stripOff();
      }
    }

    // white strobe with adjustable rate?? 
  }
   
}

void serialEvent(){
  while (Serial.available()) {
    one = Serial.parseInt();
    if (Serial.read() == '\n') {
      combination = one;
//      digitalWrite(7, proximity);      
//      digitalWrite(8, right_swipe);       
//      digitalWrite(9, left_swipe);      
//      digitalWrite(13, finger_combo);
      
    }
    
  }

}

///strip functions

//strobe function
void strobe (int red, int green, int blue) {
    for (int ledx = 0; ledx < numberOfPixels; ledx++) {  
        strip.setPixelColor(ledx, red, green, blue);   
        }
        strip.show();
}

void strobeWhite (int white) {
    for (int ledx = 0; ledx < numberOfPixels; ledx++) {  
        strip.setPixelColor(ledx, 0, 0, 0, white);   
        }
        strip.show();
}


  
// function to turn off entire strip
void stripOff() {
        for (int ledx = 0; ledx < numberOfPixels; ledx++) {
          strip.setPixelColor(ledx, 0, 0, 0);
        }
        strip.show();    
  }

// timer, changes flash state, depending on time elapsed between 2 points
void timer(int *pause, bool *flashState, unsigned long *pTime){ 
  if ((millis() - *pTime >= *pause) && (*flashState == LOW)) {
      *flashState = !*flashState;
      *pTime = millis();
    }
    else if ((millis() - *pTime >= *pause) && (*flashState == HIGH)) {
      *flashState = !*flashState;
      *pTime = millis();
    }
}


