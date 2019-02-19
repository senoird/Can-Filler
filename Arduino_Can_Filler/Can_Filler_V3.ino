int state = 0;
int val;
const int stepPin = 5; 
const int dirPin = 2; 
const int enPin = 8;
const int co2pin = 6;
const int liquid = 7;
const int level_probe = 9;
char a=0;

void setup() {
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  pinMode(co2pin, OUTPUT);
  pinMode(liquid,OUTPUT);
  pinMode(level_probe,INPUT_PULLUP);
  digitalWrite(enPin,LOW);  
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    a=Serial.read();
    if(a=='7')
    {
      if(state==0)
        {
            lower();
            delay(6000);
            fill();
            raise_();
            delay(6000);
            Serial.print(state);      
        }
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
  while(digitalRead(level_probe)==HIGH ) {
    digitalWrite(liquid,HIGH);
  }
  digitalWrite(liquid,LOW);
}
