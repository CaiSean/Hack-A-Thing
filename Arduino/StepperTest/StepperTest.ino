/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/


#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

int ledPin = 13; // choose the pin for the LED
int inPin = 5; 
int inPin2 = 2; 
int val = 0; 
int val2 = 0; 


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");

  AFMS.begin();  // create with the default frequency 1.6KHz

  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  myMotor->setSpeed(10);  // 10 rpm   
  pinMode(ledPin, OUTPUT);  // declare LED as output
  pinMode(inPin, INPUT);    // declare pushbutton as input
  pinMode(inPin2, INPUT);    // declare pushbutton as input
}

void loop() {
      
  val = digitalRead(inPin);  // read input value
  val2 = digitalRead(inPin2); 
  
  if (val == HIGH) // check if the input is HIGH (button released)
  {         
      Serial.println("Button released");
      digitalWrite(ledPin, LOW);  // turn LED OFF
      while (val == HIGH)
      {
        myMotor->release();  
        break; 
      }
  } 
  else
  {
      Serial.println("Button Pushed");
      digitalWrite(ledPin, HIGH);  // turn LED ON
      while (val == LOW)
      {
        if (val2 == HIGH)
        {
          myMotor->step(1, FORWARD, DOUBLE); 
          break; 
        }
        else
        {
          myMotor->step(1, BACKWARD, DOUBLE); 
          break; 
        }
      }
  }

}
