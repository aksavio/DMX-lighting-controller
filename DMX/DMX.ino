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


TODO:
try to make the program more scalable with structues      :Done
try to use boolean instead of integers                    :Done
*/


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
  Serial.println("Version:  0.1       Alpha ");
  Serial.println("Date:     11.01.23        ");
  Serial.println("Time:     something       ");
  
  
   void rotary_init();

}

void loop() {
  rotary1.rState = digitalRead(rotary_F);
  if (rotary1.rState != rotary1.rLastState){
    read_rotary();
  }
  
  Serial.print("Position: ");
  Serial.println(rotary1.counter);

}
