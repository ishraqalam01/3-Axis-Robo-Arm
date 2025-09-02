#include "arduino_secrets.h"

/***************
PEO SCARBOROUGH CHAPTER
Mechatronics 2024
Ontario, Canada
Lab 1 - Blinking LED

IshyVar Builders
Ishraq Alam
Varsan Jeyakkumar

****************/
#define centreLED 13

void setup() {

  pinMode(centreLED, OUTPUT);
 
  Serial.begin(9600);
  while(!Serial);
}

void loop() {

    digitalWrite(centreLED, HIGH);
    Serial.println("LED ON");
   
    delay(1000);
   
    digitalWrite(centreLED, LOW);
    Serial.println("LED OFF");
   
    delay(1000);
    
}
