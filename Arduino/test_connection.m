clear all

a = arduino('/dev/cu.usbmodem1421', 'Uno', 'Libraries', 'Adafruit\MotorShieldV2'); 


for i = 1:10
    writeDigitalPin(a, 'D13', 1); 
    pause(0.5); 
    writeDigitalPin(a, 'D13', 0); 
    pause(0.5); 
    
end

clear a