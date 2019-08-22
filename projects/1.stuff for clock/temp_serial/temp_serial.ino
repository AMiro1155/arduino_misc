float temp = 0;
int T = 0;

void setup(){
  Serial.begin(9600);
}

void loop(){
  temp = analogRead(0);
  T = (((500*temp)/1023)-50);
  Serial.println(T);
  Serial.println("C");
  delay(500);
}
