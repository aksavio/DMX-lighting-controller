/*
Author  : Akash Savio Sen
Date    : 01:01:2023
Project : DMX Controller



Modules to be used  :
RS485
Rotary encoder
OLED Display


Process:
  1. Make the rotary encoder work
      a. is it RGB or something else
      b. Change value 
  2. Learn how to make your own header files
  3. Make a Basic inerface on the OLED
      a. display the serial oitput on the oled
      


TODO:
try to make the program more scalable with structues      :Done
try to use boolean instead of integers                    :Done
*/


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     8 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Output pins of the rotary encoder
#define rotary_F 6
#define rotary_B 7
// Variables for the rotary encoder

struct rotary {
  byte counter = 0; // mode sellect
  bool rState;
  bool rLastState;
}rotary1; 


byte rgbw[4];
byte value = 0;
bool rotary_button;
unsigned long lastButtonPress = 0;

void rotary_init(){
  pinMode (rotary_F,INPUT);
  pinMode (rotary_B,INPUT);
  rotary1.rState = 0;
  rotary1.rLastState = 0;
  rotary1.rLastState = digitalRead(rotary_F); 
}

void read_rotary(){
  
     
      if (digitalRead(rotary_B) != rotary1.rState) { 
       rotary1.counter ++;
      } else {
       rotary1.counter --;
      }
     
   
   rotary1.rLastState = rotary1.rState; // Updates the previous state of the outputA with the current state
   
}


void setup() {
  Serial.begin (9600);
  //Version
  Serial.println("DMX ");
  Serial.println("Author:   Akash Savio Sen ");
  Serial.println("Version:  0.3       Alpha ");
  Serial.println("Date:     30.01.23        ");
  Serial.println("Time:     14:00 +5:30 GMT ");
  
  pinMode(4, INPUT_PULLUP);
  //Display Check
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
  Serial.println(F("SSD1306 allocation failed"));
  for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Mode Value");
  display.display();
  
  display.display();
  void rotary_init();

}

void loop() {
  rotary1.rState = digitalRead(rotary_F);
  if (rotary1.rState != rotary1.rLastState){
    read_rotary();
  }
  rotary_button = digitalRead(4);
  if (rotary_button == LOW) {
    if (millis() - lastButtonPress > 80) {
        Serial.println("Button pressed!");
    }
    lastButtonPress = millis();
    value = value++;
  }
  delay(1);
  if (value > 3){
    value = 0;
  }

 
  Serial.print("Position: ");
  
  Serial.println(rotary1.counter);
  Serial.println(value);
  rgbw[value] = rotary1.counter;
  display.clearDisplay();


  
  display.setCursor(0,0);
  display.print("Red    ");
  display.println(rgbw[0]);
  display.print("Green  ");
  display.println(rgbw[1]);
  display.print("Blue   ");
  display.println(rgbw[2]);
  display.print("White  ");
  display.println(rgbw[3]);
  
  display.display();

}
