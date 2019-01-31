
int state;
int last_state = 1;
int val;
const int stepPin = 5; 
const int dirPin = 2; 
const int enPin = 8;
const int co2pin = 6;
const int liquid = 7;
const int level_probe = 9;

void setup() {
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
        if (last_state != 2){
          raise_();
          delay(1000);
          last_state = state;
          Serial.println(last_state);
        }
        else{
          Serial.println("Already in raised state");         
        }
      }
      if (state == 1){
        if (last_state != 1){
          if (last_state != 2){
            fill();
            delay(1000);
            last_state = state;
            Serial.println(last_state);
            }
        }
        else{
          Serial.println("Already in fill state");
        }
      }
      if (state == 0){
        if (last_state != 0){
          lower();
          delay(1000);
          last_state = state;
          Serial.println(last_state);
        }
        else{
          Serial.println("Already in lowered state");       
        }
      }
    }
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}
void raise_() {
  digitalWrite(dirPin,HIGH); 
  for(int x = 0; x < 3810; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
}
void lower() {
  digitalWrite(dirPin,LOW); 
  for(int x = 0; x < 3810; x++) {
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
