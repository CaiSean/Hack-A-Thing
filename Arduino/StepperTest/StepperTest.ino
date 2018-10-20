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
Adafruit_MotorShield AFMS1 = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *stepperMotor = AFMS1.getStepper(200, 2);

// INPUT Hardwares
int main_switch = 2; 
int stepper_dir_switch = 3; 
int push_button = 5; 

// OUTPUT Hardware
int ledPin = 13; 

int val_main_switch = 0; 
int val_step_dir_switch = 0; 
int PB_state = 0; 
int step_length[] = {5705, 3300, 7220, 6016, 2812, 3412, 4000};


void setup() {
  Serial.begin(9600);
  AFMS1.begin();   

  // turn on stepper motor
  stepperMotor->setSpeed(1200);  // 1200 rpm 
  stepperMotor->step(50, FORWARD, SINGLE);
  stepperMotor->step(50, BACKWARD, SINGLE);

  pinMode(ledPin, OUTPUT);  // declare LED as output
  pinMode(main_switch, INPUT);    // declare switch as input
  pinMode(stepper_dir_switch, INPUT);    // declare switch as input
  pinMode(push_button, INPUT); 
}

void loop() {
  stepper_motor(); 
  
  PB_state = digitalRead(push_button); 

  if (PB_state == HIGH)
  {
    stepperMotor->setSpeed(800);
    stepperMotor->step(600, BACKWARD, DOUBLE); 
    stepperMotor->step(920, FORWARD, DOUBLE); 
    
    stepperMotor->setSpeed(2000);
    stepperMotor->step(step_length[1]+320, BACKWARD, DOUBLE);
    stepperMotor->release(); 
  }

}

void stepper_motor()
{
  stepperMotor->setSpeed(2000);
  
  val_main_switch = digitalRead(main_switch);  // read input value
  val_step_dir_switch = digitalRead(stepper_dir_switch);  // read input value
  
  if (val_main_switch == HIGH) // check if the input is HIGH (switch OFF)
  {         
    // Serial.println("Stepper power switch OFF");
    digitalWrite(ledPin, LOW);  // turn LED OFF
    while (val_main_switch == HIGH)
    {
      stepperMotor->release();  
      break; 
    }
  } 
  else
  {
    // Serial.println("Stepper power switch ON");
    digitalWrite(ledPin, HIGH);  // turn LED ON
    while (val_main_switch == LOW)
    {
      if (val_step_dir_switch == HIGH)
      {
        // Serial.println("Stepper motor FORWARD");
        stepperMotor->step(50, FORWARD, SINGLE); 
        break; 
      }
      else
      {
        // Serial.println("Stepper motor BACKWARD");
        stepperMotor->step(50, BACKWARD, SINGLE); 
        break; 
      }
    }
  }
}
