
int led = 13;
int state;
int val;
const int stepPin = 5; 
const int dirPin = 2; 
const int enPin = 8;
const int co2pin = 6;
const int liquid = 7;
const int level_probe = 9;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  pinMode(co2pin, OUTPUT);
  pinMode(liquid,OUTPUT);
  pinMode(level_probe,INPUT_PULLUP);
  digitalWrite(enPin,LOW);  
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    if (Serial.peek() == 'c') {
      Serial.read();
      state = Serial.parseInt();
      if (state == 2){
        raise_();
        delay(1000);
      }
      if (state == 1){
        fill();
        delay(1000);
      }
      if (state == 0){
        lower();
        delay(1000);
      }
    }
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}
void raise_() {
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 800; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
}
void lower() {
  digitalWrite(dirPin,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 800; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
  }
}
void fill(){
  digitalWrite(co2pin,HIGH);
  delay(5000);
  digitalWrite(co2pin,LOW);
  //val = digitalRead(level_probe);
  //Serial.println(val);
  while(digitalRead(level_probe)==HIGH ) {
    digitalWrite(liquid,HIGH);
  }
  digitalWrite(liquid,LOW);
}
