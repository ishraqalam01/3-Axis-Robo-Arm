#include "arduino_secrets.h"

/********************************
  PEO Scarborough Chapter
  Mechatronics 2024
  Ontario, Canada
  Lab 5 - Joystick Servo Control

  IshyVar Builders
  Ishraq Alam
  Varsan Jeyakkumar
********************************/

#include <ESP32Servo.h>

#define buttonPin 25
#define joystickXPin 35
#define joystickYPin 34

bool buttonState = HIGH; 
bool buttontoggle = HIGH;

Servo servoX;
Servo servoY;
Servo servoG;

int minUs = 520;      
int maxUs = 2480;

int servoXPin = 18;
int servoYPin = 19;
int servoGPin = 21;

int servoXPos = 0;                   
int servoYPos = 0;                   
int servoGPos = 0;   

int servoXPos_min = 0;
int servoXPos_max = 180;    

int servoYPos_min = 0;        
int servoYPos_max = 180;    

int servoGPos_min = 0;        
int servoGPos_max = 180;

int joystickXValue = 0;
int joystickYValue = 0;

void setup() {

  pinMode(buttonPin, INPUT_PULLUP);

  servoX.attach(servoXPin, minUs, maxUs);
  servoY.attach(servoYPin, minUs, maxUs);
  servoG.attach(servoGPin, minUs, maxUs);

  servoX.write(servoXPos_min);
  servoY.write(servoYPos_min);
  servoG.write(servoGPos_min);
  
  Serial.begin(9600);
  while(!Serial);
  
}

void loop() {
  
  buttonState = digitalRead(buttonPin);
  joystickXValue = analogRead(joystickXPin);
  joystickYValue = analogRead(joystickYPin);

  if (!buttonState) {

    if (buttontoggle) {
  
      for (servoGPos = servoGPos_min; servoGPos < servoGPos_max; servoGPos += 1) { 
        servoG.write(servoGPos);
	    delay(1); 
      }
    
    }

    if (!buttontoggle) {
      
      for (servoGPos = servoGPos_max; servoGPos > servoGPos_min;servoGPos -= 1) {
  	    servoG.write(servoGPos);
  	    delay(1);
      } 
      
    }
    
    Serial.println("Current Reading >>");    
    Serial.print("X Value: ");
    Serial.println(joystickXValue);
    Serial.print("Y Value: ");
    Serial.println(joystickYValue);
    
    buttonState = HIGH;
    buttontoggle = !buttontoggle;
    
    delay(250);
    
  } 

  // Move Base to Right
  if (joystickXValue > 3000 && 1000 < joystickYValue < 3000) {
    
    if (servoXPos < servoXPos_max) {
      servoXPos++;
      servoX.write(servoXPos);
    }
    delay(10); 
    
  }
   
  // Move Base to Left
  if (joystickXValue < 1000 && 1000 < joystickYValue < 3000) {

    if (servoXPos > servoXPos_min) {
      servoXPos--;
      servoX.write(servoXPos);
    }
    delay(10);  
    
  }

  // Move Arm Up 
  if (1000 < joystickXValue < 3000 && joystickYValue < 1000) {
    
    if (servoYPos < servoYPos_max) {
      servoYPos++;
      servoY.write(servoYPos);
    }
    delay(10);    
    
  }
   
  // Move Arm Down 
  if (1000 < joystickXValue < 3000 && joystickYValue > 3000) {
    
    if (servoYPos > servoYPos_min) {
      servoYPos--;
      servoY.write(servoYPos);
    }
    delay(10);  
    
  }

  
} // Void