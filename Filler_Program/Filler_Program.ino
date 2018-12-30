/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
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

// the loop function runs over and over again forever
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
