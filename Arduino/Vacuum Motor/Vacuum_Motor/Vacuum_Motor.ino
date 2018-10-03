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

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

int ledPin = 13; // choose the pin for the LED
int inPin = 3; 
int val = 0; 

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(255);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);

  pinMode(ledPin, OUTPUT);  // declare LED as output
  pinMode(inPin, INPUT);    // declare pushbutton as input
}

void loop() {
//  uint8_t i;
  val = digitalRead(inPin);  // read input value

  if (val == HIGH)
  {
    Serial.println("Switch OFF"); 
    digitalWrite(ledPin, LOW);  // turn LED OFF
      while (val == HIGH)
      {
        //vac_release();  
        myMotor->run(RELEASE); 
        break; 
      }
  }
  else
  {
    Serial.println("Switch ON");
      digitalWrite(ledPin, HIGH);  // turn LED ON
      while (val == LOW)
      {
        
        myMotor->run(FORWARD);
        break; 
      }
  }
 
//  delay(10);


}

void vac_release()
{
  myMotor->run(BACKWARD); 
  myMotor->setSpeed(100); 
  delay(100); 
  myMotor->run(RELEASE); 
}

