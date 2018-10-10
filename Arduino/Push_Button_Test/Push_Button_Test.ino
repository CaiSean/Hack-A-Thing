int push_button = 8; 
int ledPin = 13; 

int val = 0; 

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT); 
  pinMode(push_button, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(push_button); 

  if (val == LOW)
  {
    digitalWrite(ledPin, LOW);
  }
  else
  {
    digitalWrite(ledPin, HIGH);
  }
}
