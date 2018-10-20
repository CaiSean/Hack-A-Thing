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
int flag = 0; 
int step_length[] = {5705+150, 3300, 7220+150, 6016-100, 2812, 3412, 4000};

void check_robot_pos(); 
void vacuum_motor(); 

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
        stepperMotor->step(50, FORWARD, DOUBLE); 
        break; 
      }
      else
      {
        // Serial.println("Stepper motor BACKWARD");
        stepperMotor->step(50, BACKWARD, DOUBLE); 
        break; 
      }
    }
  }
}

void auto_feeding()
{
  int PB_state = LOW; 
  PB_state = digitalRead(push_button); 

  if (PB_state == HIGH)
  {
    digitalWrite(ledPin, HIGH);
    
    for (int i = 0; i < 7; i++)
    {
      Serial.println(i);
      flag = 0; 
      while (flag == 0)
      {
        check_robot_pos(); 
      }
      delay(100); 
      
      if (flag == 1)
      {
        myServo.write(120);
        vacMotor->run(FORWARD);
        
        stepperMotor->setSpeed(800);
        stepperMotor->step(500, BACKWARD, DOUBLE); 
        stepperMotor->step(820, FORWARD, DOUBLE); 
        // This will take 6.51 seconds

        if (i == 5)
        {
          stepperMotor->step(800, BACKWARD, DOUBLE); 
          stepperMotor->step(800, FORWARD, DOUBLE); 
          stepperMotor->step(800, BACKWARD, DOUBLE); 
          stepperMotor->step(800, FORWARD, DOUBLE); 
        }
        // This takes 13 seconds
        
        stepperMotor->setSpeed(2000);
        stepperMotor->step(step_length[i]+320, BACKWARD, DOUBLE);
        Serial.println(step_length[i]);  
         
        if (i == 0)
        {
          delay(11730+6500); 
          vacMotor->run(RELEASE);
          myServo.write(160);
        }
        else if (i == 1)
        {
          delay(21690+6500); 
          vacMotor->run(RELEASE);
          myServo.write(160);
        }
        else if (i == 2)
        {
          delay(5790+6500); 
          vacMotor->run(RELEASE);
          myServo.write(160);
        }
        else if (i == 3)
        {
          delay(10800+6500); 
          vacMotor->run(RELEASE);
          myServo.write(160);
        }
        else if (i == 4)
        {
          delay(23630+6500); 
          vacMotor->run(RELEASE);
          myServo.write(160);
        }
        else if (i == 5)
        {
          delay(7700+6500); 
          vacMotor->run(RELEASE);
          myServo.write(160);
        }
        else if (i == 6)
        {
          delay(18670+6500); 
          vacMotor->run(RELEASE);
          myServo.write(160);
        }
      }
      
    }
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
    // Serial.println("Vacuum Switch OFF"); 
    myServo.write(160);
   
    while (val_vac_switch == HIGH)
    { 
      vacMotor->run(RELEASE); 
      break;
    }
  }
  else
  {
    // Serial.println("Vacuum Switch ON");
    myServo.write(120);

    while (val_vac_switch == LOW)
    {
      vacMotor->run(FORWARD);        
      break; 
    }
  }
}

void check_robot_pos()
{
  lightLevel = analogRead(photoResistorPin); 
  lightLevel = map(lightLevel, 0, 1023, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);

  int threshold  = 120; 
  
  if (lightLevel < threshold)
  {
    flag = 1; 
  }
  else 
  {
    flag = 0;   
  }
}

