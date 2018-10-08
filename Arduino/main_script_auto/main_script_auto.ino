#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>

Adafruit_MotorShield AFMS1 = Adafruit_MotorShield();
Adafruit_MotorShield AFMS2 = Adafruit_MotorShield(); 

// initiate DC motor at port 1 (M1)
Adafruit_DCMotor *vacMotor = AFMS1.getMotor(1); 
// initiate Stepper motor at port 2 (M3 and M4)
Adafruit_StepperMotor *stepperMotor = AFMS2.getStepper(200, 2); 
Servo myServo;  // create a servo object

int main_switch = 5; 
int ledPin = 13; 

int val_main_switch = 0; 

void setup() {
  Serial.begin(9600);
  AFMS1.begin();  
  AFMS2.begin(); 

  // turn on DC motor
  vacMotor->setSpeed(255); // PWM from 0 to 255
  vacMotor->run(FORWARD);
  vacMotor->run(RELEASE);

  // turn on stepper motor
  stepperMotor->setSpeed(200);  // 120 rpm 

  // initiate servo motor
  myServo.attach(7); // attaches the servo on pin 7 to the servo object

  pinMode(ledPin, OUTPUT);  // declare LED as output
  pinMode(main_switch, INPUT);    // declare switch as input
//  pinMode(stepper_dir_switch, INPUT);    // declare switch as input
//  pinMode(vac_switch, INPUT);    // declare switch as input
  delay(1000); 
}

void loop() {
  val_main_switch = digitalRead(main_switch); 

  if (val_main_switch == LOW)
  {
    digitalWrite(ledPin, HIGH); 
    // Sticker 1
//    stepperMotor->step(5000, FORWARD, SINGLE); 
//    gap_step(); 
    
    // Sticker 2
    stepperMotor->step(2975, BACKWARD, SINGLE); 
    delay(2000);
    gap_step(); 
    
    // Sticker 3
    stepperMotor->step(6825, BACKWARD, SINGLE); 
    delay(2000);
    gap_step(); 
    
    // Sticker 4
    stepperMotor->step(5650, BACKWARD, SINGLE); 
    gap_step(); 
    
    // Sticker 5
    stepperMotor->step(2480, BACKWARD, SINGLE); 
    gap_step(); 
    
    // Sticker 6
    stepperMotor->step(3094, BACKWARD, SINGLE); 
    delay(2000);
    gap_step(); 
    
    // Sticker 7
    stepperMotor->step(6213, BACKWARD, SINGLE); 
    delay(2000);
    gap_step(); 
    
    // Sticker 8
    stepperMotor->step(2225, BACKWARD, SINGLE);  
    delay(2000);

    stepperMotor->release();
  }

}

void gap_step()
{
  stepperMotor->step(235, FORWARD, SINGLE); 
}

