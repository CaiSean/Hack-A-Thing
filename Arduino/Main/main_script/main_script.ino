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

int stepper_pow_switch = 5; 
int stepper_dir_switch = 2; 
int vac_switch = 3; 
int ledPin = 13; // choose the pin for the LED

int val_vac_switch = 0; 
int val_step_pow_switch = 0; 
int val_step_dir_switch = 0; 

void setup() {
  Serial.begin(9600);
  AFMS1.begin();  
  AFMS2.begin(); 

  // turn on DC motor
  vacMotor->setSpeed(255); // PWM from 0 to 255
  vacMotor->run(FORWARD);
  vacMotor->run(RELEASE);

  // turn on stepper motor
  stepperMotor->setSpeed(120);  // 10 rpm 

  // initiate servo motor
  myServo.attach(7); // attaches the servo on pin 7 to the servo object

  pinMode(ledPin, OUTPUT);  // declare LED as output
  pinMode(stepper_pow_switch, INPUT);    // declare switch as input
  pinMode(stepper_dir_switch, INPUT);    // declare switch as input
  pinMode(vac_switch, INPUT);    // declare switch as input
  delay(1000); 
}

void loop() {
  stepper_motor();
  vacuum_motor(); 
  //vacuum_suction(vacuum_motor());
}

void stepper_motor()
{
  val_step_pow_switch = digitalRead(stepper_pow_switch);  // read input value
  val_step_dir_switch = digitalRead(stepper_dir_switch);  // read input value
  
  if (val_step_pow_switch == HIGH) // check if the input is HIGH (switch OFF)
  {         
    Serial.println("Stepper power switch OFF");
    digitalWrite(ledPin, LOW);  // turn LED OFF
    while (val_step_pow_switch == HIGH)
    {
      stepperMotor->release();  
      break; 
    }
  } 
  else
  {
    Serial.println("Stepper power switch ON");
    digitalWrite(ledPin, HIGH);  // turn LED ON
    while (val_step_pow_switch == LOW)
    {
      if (val_step_dir_switch == HIGH)
      {
        Serial.println("Stepper motor FORWARD");
        stepperMotor->step(15, FORWARD, SINGLE); 
        break; 
      }
      else
      {
        Serial.println("Stepper motor BACKWARD");
        stepperMotor->step(15, BACKWARD, SINGLE); 
        break; 
      }
    }
  }
  // delay(10);
}

void vacuum_motor()
{
    val_vac_switch = digitalRead(vac_switch);  // read input value

  if (val_vac_switch == HIGH)
  {
    Serial.println("Vacuum Switch OFF"); 
    myServo.write(150);
    // digitalWrite(ledPin, LOW);  // turn LED OFF
      while (val_vac_switch == HIGH)
      { 
        vacMotor->run(RELEASE); 
        break;
      }
  }
  else
  {
    Serial.println("Vacuum Switch ON");
    myServo.write(120);
      // digitalWrite(ledPin, HIGH);  // turn LED ON
      while (val_vac_switch == LOW)
      {
        vacMotor->run(FORWARD);
        
        break; 
      }
  }
}


