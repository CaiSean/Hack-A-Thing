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

// INPUT Hardwares
int main_switch = 2; 
int stepper_dir_switch = 3; 
int vac_switch = 4; 
int push_button = 5; 
int photoResistorPin = 1; 

// OUTPUT Hardware
int ledPin = 13; 

int val_main_switch = 0; 
int val_step_dir_switch = 0; 
int val_vac_switch = 0; 
int lightLevel; 
int step_length[] = {3340, 7264, 6066-302, 2822, 3462, 6636-3000}; 

void setup() {
  Serial.begin(9600);
  AFMS1.begin();  
  AFMS2.begin(); 

  // turn on stepper motor
  stepperMotor->setSpeed(1200);  // 1200 rpm 
  stepperMotor->step(50, FORWARD, SINGLE);
  stepperMotor->step(50, BACKWARD, SINGLE);

  // turn on DC motor
  vacMotor->setSpeed(150); // PWM from 0 to 255
  vacMotor->run(FORWARD); 
  delay(100); 
  vacMotor->run(RELEASE); 
  vacMotor->setSpeed(255);

  // initiate servo motor
  myServo.attach(9); // attaches the servo on pin 9 to the servo object
  myServo.write(0);
  delay(1000);
  myServo.write(160);

  pinMode(ledPin, OUTPUT);  // declare LED as output
  pinMode(main_switch, INPUT);    // declare switch as input
  pinMode(stepper_dir_switch, INPUT);    // declare switch as input
  pinMode(push_button, INPUT); 
  pinMode(vac_switch, INPUT);    // declare switch as input
}

void loop() {
  stepper_motor(); 
  auto_feeding(); 
  vacuum_motor(); 
}

void stepper_motor()
{
  stepperMotor->setSpeed(2000);
  
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
        stepperMotor->step(50, FORWARD, SINGLE); 
        break; 
      }
      else
      {
        Serial.println("Stepper motor BACKWARD");
        stepperMotor->step(50, BACKWARD, SINGLE); 
        break; 
      }
    }
  }
}

void auto_feeding()
{
  stepperMotor->setSpeed(1200);
  int PB_state = 0; 

  PB_state = digitalRead(push_button); 

  if (PB_state == HIGH)
  {
    digitalWrite(ledPin, HIGH);
    
    // Part of Sticker 1 
    // stepperMotor->step(3258, BACKWARD, DOUBLE); 
//    myServo.write(128);
//    vacMotor->run(FORWARD);
//    stepperMotor->step(250*1.5, BACKWARD, DOUBLE); // move 2 mm front
//    // check_sticker(); 
//    delay(10000);
//    vacMotor->run(RELEASE);
//    myServo.write(160);
    // Sticker 2
    myServo.write(128);
    vacMotor->run(FORWARD);
    stepperMotor->step(3340, BACKWARD, DOUBLE);
    // check_sticker(); 
    delay(12000);
     
    check_sticker();
    //delay(10000);
    delay(2000);
    
    // Sticker 3
    stepperMotor->step(7264, BACKWARD, DOUBLE);
    check_sticker();
    //delay(10000); 
    delay(2000);
    
    // Sticker 4
    stepperMotor->step(6066-302, BACKWARD, DOUBLE); 
    check_sticker();
    //delay(10000); 
    delay(2000);
    
    // Sticker 5
    stepperMotor->step(2822, BACKWARD, DOUBLE); 
    check_sticker();
    //delay(10000);
    delay(2000);
    
    // Sticker 6
    stepperMotor->step(3462, BACKWARD, DOUBLE); 
    check_sticker();
    //delay(10000); 
    delay(2000);
    
    // Sticker 7
    stepperMotor->step(6636-3000, BACKWARD, DOUBLE); 
    check_sticker();
    vacMotor->run(RELEASE);
    myServo.write(160);
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

void vacuum_motor()
{
   val_vac_switch = digitalRead(vac_switch);  // read input value

  if (val_vac_switch == HIGH)
  {
    Serial.println("Vacuum Switch OFF"); 
    myServo.write(160);
   
    while (val_vac_switch == HIGH)
    { 
      vacMotor->run(RELEASE); 
      break;
    }
  }
  else
  {
    Serial.println("Vacuum Switch ON");
    myServo.write(128);

    while (val_vac_switch == LOW)
    {
      vacMotor->run(FORWARD);        
      break; 
    }
  }
}

void check_sticker()
{
  lightLevel = analogRead(photoResistorPin); 
  lightLevel = map(lightLevel, 0, 1023, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);

  int threshold  = 170; 
  
  if (lightLevel > threshold)
  {
    for (int i = 0; i < 3; i++)
    {
      stepperMotor->step(400, BACKWARD, DOUBLE); 
      stepperMotor->step(400, FORWARD, DOUBLE); 
    }
  }
  else 
  {
    stepperMotor->release();  
  }
  
}

