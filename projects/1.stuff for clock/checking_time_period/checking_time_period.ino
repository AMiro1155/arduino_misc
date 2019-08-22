int sig = 12;
long current = 0;
long old = 0;
long T = 0;
void setup(){
  Serial.begin(9600);
  pinMode(sig, INPUT);
}

void loop(){
  
  
  if (digitalRead(sig) == HIGH){
   old = millis();
  }
  if (digitalRead(sig) == LOW){
   current = millis();
   T = (current - old);
  }
Serial.println(T);
}
