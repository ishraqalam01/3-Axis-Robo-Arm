#include "arduino_secrets.h"

/*
PEO Scarborough Chapter
  Mechatronics 2024
  Ontario, Canada
  Lab 3 - Joystick LED Control

  IshyVar Builders
  Ishraq Alam
  Varsan Jeyakkumar
*/
#define buttonPin 25
#define centreLED 13
#define rightLED 27
#define leftLED 26
#define bottomLED 14
#define topLED 12
#define joystickXPin 35
#define joystickYPin 34

bool buttonState = HIGH;  

int joystickXValue = 0;
int joystickYValue = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(centreLED, OUTPUT);
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  pinMode(bottomLED, OUTPUT);
  pinMode(topLED, OUTPUT);
  
  Serial.begin(9600);
  while(!Serial);
}

void loop() {
    buttonState = digitalRead(buttonPin);
  joystickXValue = analogRead(joystickXPin);
  joystickYValue = analogRead(joystickYPin);

  if (!buttonState) {

    digitalWrite(centreLED, HIGH);
    
    Serial.println("Current Reading >>");    
    Serial.print("X Value: ");
    Serial.println(joystickXValue);
    Serial.print("Y Value: ");
    Serial.println(joystickYValue);
    
    buttonState = HIGH;
    
    delay(250);
    
  } else {
    
    digitalWrite(centreLED, LOW);
  
  }
 
  // Right LED
  if (joystickXValue > 3000 && 1000 < joystickYValue < 3000) {
    
    digitalWrite(centreLED, LOW);
    digitalWrite(topLED, LOW);
    digitalWrite(bottomLED, LOW);
    digitalWrite(rightLED, HIGH);
    digitalWrite(leftLED, LOW);   
    
  }

  // Left LED
  if (joystickXValue < 1000 && 1000 < joystickYValue < 3000) {

    digitalWrite(centreLED, LOW);
    digitalWrite(topLED, LOW);
    digitalWrite(bottomLED, LOW);
    digitalWrite(rightLED, LOW);
    digitalWrite(leftLED, HIGH);   
    
  }

  // Top LED 
  if (1000 < joystickXValue < 3000 && joystickYValue < 1000) {
    
    digitalWrite(centreLED, LOW);
    digitalWrite(topLED, HIGH);
    digitalWrite(bottomLED, LOW);
    digitalWrite(rightLED, LOW);
    digitalWrite(leftLED, LOW);   
  }
   
  // Bottom LED 
  if (1000 < joystickXValue < 3000 && joystickYValue > 3000) {
    
    digitalWrite(centreLED, LOW);
    digitalWrite(topLED, LOW);
    digitalWrite(bottomLED, HIGH);
    digitalWrite(rightLED, LOW);
    digitalWrite(leftLED, LOW);   
  }
}
