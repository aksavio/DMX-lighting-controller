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



TODO:
try to make the program more scalable with structues
try to use boolean instead of integers
*/


// Output pins of the rotary encoder
#define outputA 6
#define outputB 7
// Variables for the rotary encoder

struct rotary {
  int counter = 0; // mode sellect
  int rState;
  int rLastState;
}
// Mode will be the DMX channel of the light

void setup() {
  Serial.begin (9600);
  //Version
  Serial.println("DMX ");
  Serial.println("Author:   Akash Savio Sen ");
  Serial.println("Version:  1.0       Alpha ");
  Serial.println("Date:     11.01.23        ");
  Serial.println("Time:     something       ");
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  rLastState = digitalRead(outputA);  

}

void loop() {
  rState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (rState != rLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != rState) { 
       counter ++;
     } else {
       counter --;
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   rLastState = rState; // Updates the previous state of the outputA with the current state
  


}
