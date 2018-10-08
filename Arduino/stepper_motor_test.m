clear all

a = arduino('/dev/cu.usbmodem1421', 'Uno', 'Libraries', 'Adafruit\MotorShieldV2'); 

shield = addon(a,'Adafruit/MotorShieldV2');
sm = stepper(shield, 2, 200, 'RPM', 100); 

move(sm, 100);