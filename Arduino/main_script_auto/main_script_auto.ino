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
int stepper_dir_switch = 2; 
int ledPin = 13; 
int push_button = 8; 

int val_main_switch = 0; 
int val_step_dir_switch = 0; 
int PB_state = 0; 

void setup() {
  Serial.begin(9600);
  AFMS1.begin();  
  AFMS2.begin(); 

  // turn on DC motor
  vacMotor->setSpeed(255); // PWM from 0 to 255
  vacMotor->run(FORWARD);
  vacMotor->run(RELEASE);

  // turn on stepper motor
  stepperMotor->setSpeed(1200);  // 120 rpm 

  // initiate servo motor
  myServo.attach(7); // attaches the servo on pin 7 to the servo object
  myServo.write(0);
  delay(1000);
  myServo.write(150);

  pinMode(ledPin, OUTPUT);  // declare LED as output
  pinMode(main_switch, INPUT);    // declare switch as input
  pinMode(stepper_dir_switch, INPUT);    // declare switch as input
  pinMode(push_button, INPUT); 
//  pinMode(vac_switch, INPUT);    // declare switch as input
  delay(1000); 
}

void loop() {
  stepper_motor(); 
  auto_feeding(); 
}

void stepper_motor()
{
  stepperMotor->setSpeed(1200);
  
  val_main_switch = digitalRead(main_switch);  // read input value
  val_step_dir_switch = digitalRead(stepper_dir_switch);  // read input value
  
  if (val_main_switch == HIGH) // check if the input is HIGH (switch OFF)
  {         
    Serial.println("Stepper power switch OFF");
    digitalWrite(ledPin, LOW);  // turn LED OFF
    while (val_main_switch == HIGH)
    {
      stepperMotor->release();  
      break; 
    }
  } 
  else
  {
    Serial.println("Stepper power switch ON");
    digitalWrite(ledPin, HIGH);  // turn LED ON
    while (val_main_switch == LOW)
    {
      if (val_step_dir_switch == HIGH)
      {
        Serial.println("Stepper motor FORWARD");
        stepperMotor->step(30, FORWARD, SINGLE); 
        break; 
      }
      else
      {
        Serial.println("Stepper motor BACKWARD");
        stepperMotor->step(30, BACKWARD, SINGLE); 
        break; 
      }
    }
  }
  // delay(10);
}

void auto_feeding()
{
  stepperMotor->setSpeed(1200);
  PB_state = 0; 

  PB_state = digitalRead(push_button); 

  if (PB_state == HIGH)
  {
    digitalWrite(ledPin, HIGH);
    // Part of Sticker 1 
    stepperMotor->step(3258, BACKWARD, SINGLE); 
    delay(2000);
    
    // Sticker 2
    stepperMotor->step(3340, BACKWARD, SINGLE); 
    //delay(10000);
    delay(2000);
    
    // Sticker 3
    // Lift time: 27.20 seconds
    stepperMotor->step(7264, BACKWARD, SINGLE);
    //delay(10000); 
    delay(2000);
    
    // Sticker 4
    stepperMotor->step(6066-302, BACKWARD, SINGLE); 
    //delay(10000); 
    delay(2000);
    
    // Sticker 5
    stepperMotor->step(2822, BACKWARD, SINGLE); 
    //delay(10000);
    delay(2000);
    
    // Sticker 6
    stepperMotor->step(3462, BACKWARD, SINGLE); 
    //delay(10000); 
    delay(2000);
    
    // Sticker 7
    stepperMotor->step(6636-3000, BACKWARD, SINGLE); 
    //delay(10000);
    delay(2000);
    
    stepperMotor->release();

    PB_state = LOW; 
  }
  else
  {
    stepperMotor->release();  
  }
  
  PB_state = LOW; 
}

