int sensorPin = 1; 
int ledPin = 13; 

int lightLevel; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); 
  
}

void loop() {
  // put your main code here, to run repeatedly:
  lightLevel = analogRead(sensorPin); 
  
  lightLevel = map(lightLevel, 0, 1023, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);
  
  Serial.println(lightLevel); 
}
