int an0 = 12;
int an1 = 11;
int a = 10;
int b = 9;
int c = 8;
int d = 7;
int e = 6;
int f = 5;
int g = 4;

void setup(){
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(an0, OUTPUT);
  pinMode(an1, OUTPUT);
}

void loop(){
  digitalWrite(an0, HIGH);
  digitalWrite(an1,LOW);
  delay(25);
  digitalWrite(an0,LOW);
  digitalWrite(an1,HIGH);
  delay(25);
}
