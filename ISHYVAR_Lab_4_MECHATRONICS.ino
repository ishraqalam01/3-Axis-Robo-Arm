#include "arduino_secrets.h"

/********************************
  PEO Scarborough Chapter
  Mechatronics 2024
  Ontario, Canada
  Lab 4 - Servo Sweep

  IshyVar Builders
  Ishraq Alam
  Varsan Jeyakkumar
********************************/

#include <ESP32Servo.h>

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

void setup() {  
 
  servoX.attach(servoXPin, minUs, maxUs);
  servoY.attach(servoYPin, minUs, maxUs);
  servoG.attach(servoGPin, minUs, maxUs);
  
  Serial.begin(9600);
  while(!Serial);
  
}

void loop() {
  
  for (servoXPos = servoXPos_min; servoXPos < servoXPos_max; servoXPos += 1) {
	servoX.write(servoXPos);
	delay(15);             
  }
  for (servoXPos = servoXPos_max; servoXPos > servoXPos_min; servoXPos -= 1) { 
	servoX.write(servoXPos);
	delay(15);
  }
  
  for (servoYPos = servoYPos_min; servoYPos < servoYPos_max; servoYPos += 1) { 
	servoY.write(servoYPos);
	delay(15);           
  }
  for (servoYPos = servoYPos_max; servoYPos > servoYPos_min; servoYPos -= 1) { 
	servoY.write(servoYPos);
	delay(15);
  }  
  
  for (servoGPos = servoGPos_min; servoGPos < servoGPos_max; servoGPos += 1) { 
	servoG.write(servoGPos);
	delay(15);            
  }
  for (servoGPos = servoGPos_max; servoGPos > servoGPos_min; servoGPos -= 1) { 
	servoG.write(servoGPos);
	delay(15);
  } 
  
} //Void