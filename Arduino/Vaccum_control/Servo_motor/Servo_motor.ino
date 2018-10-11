/*
  Arduino Starter Kit example
 Project 5  - Servo Mood Indicator

 This sketch is written to accompany Project 5 in the
 Arduino Starter Kit

 Parts required:
 servo motor
 10 kilohm potentiometer
 2 100 uF electrolytic capacitors

 Created 13 September 2012
 by Scott Fitzgerald

 http://www.arduino.cc/starterKit

 This example code is part of the public domain
 */

// include the servo library
#include <Servo.h>

Servo myServo;  // create a servo object

int angle;   // variable to hold the angle for the servo motor
int inPin = 3; 
int val = 0; 

void setup() {
  myServo.attach(9); // attaches the servo on pin 9 to the servo object
  Serial.begin(9600); // open a serial connection to your computer
  pinMode(inPin, INPUT); 
}

void loop() {
  
  // set the servo position
  val = digitalRead(inPin); 
  if (val == HIGH)
  {
    myServo.write(120);
  }
  else 
  {
    myServo.write(150);
  }
    

}


