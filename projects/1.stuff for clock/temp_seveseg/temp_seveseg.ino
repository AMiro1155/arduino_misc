byte states[11] = {0x80, 0xf2, 0x48, 0x60, 0x32, 0x24, 0x04, 0xf0, 0x00, 0x20, 0x8c};
int degree = 0;
int tens_degree = 0;
float voltage = 0;
int temper = 0;
int calib_T = 0;

void setup(){
  DDRD = DDRD | B11111110;//setting up pins 7-1 as outputs
  DDRB = DDRB | B00101111;//setting up pins 8-11 as outputs
}

//Display control function
void display1(){
      PORTB = B00000100;//3rd digit high
      PORTD = states[tens_degree];
      delay(1);
      PORTB = B00000010;//2nd digit high
      PORTD = states[degree];
      delay(1);
      PORTB = B00100000;//apostrophe
      delay(1);
      PORTB = B00000001;//C
      PORTD = states[10];
      delay(1);
      PORTB = B00000000;//brightness
      delay(1);
}

void temp(){
   temper = analogRead(5);
   voltage = temper * 5.0;
   voltage /= 1023.0;
   int T = (voltage - 0.5) * 100;
   calib_T = T - 10;
   
   tens_degree = calib_T/10;
   degree = calib_T - (tens_degree *10);

}

void loop(){
  temp();
  display1();
}
