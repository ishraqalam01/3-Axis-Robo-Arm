#include "arduino_secrets.h"

/*
PEO Scarborough Chapter
Mechatronics 2024
Ontario, Canada
Lab 2 - Joystick Pushbutton

IshyVar Builders
Ishraq Alam
Varsan Jeyakkumar
*/

#define buttonPin 25
#define centreLED 13

bool buttonState = HIGH; 

void setup() {

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(centreLED, OUTPUT);

  Serial.begin(9600);
  while(!Serial);
}

void loop() {

  buttonState = digitalRead(buttonPin);
      
  if (!buttonState) {
    
    digitalWrite(centreLED, HIGH);
    Serial.println("LED ON");
    
    delay(250);
    
  } else {
    
    digitalWrite(centreLED, LOW);
    Serial.println("LED OFF");

    }
    
}
