//Setting up array with segment values
byte states[10] = {0x80, 0xf2, 0x48, 0x60, 0x32, 0x24, 0x04, 0xf0, 0x00, 0x20};

//Values for digits
int minutes = 0;
int tens_minutes = 0;
int hours = 0;
int tens_hours = 0;

int button = 14;
int button2 = 15;
//Setting up registers
void setup(){
  DDRD = DDRD | B11111110;//setting up pins 7-1 as outputs
  DDRB = DDRB | B00001111;//setting up pins 8-11 as outputs
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
  pinMode(button2, INPUT);
  digitalWrite(button2, HIGH);
} 

void debounce(){
 boolean button_old = digitalRead(button);
 delay(10);
 boolean button_new = digitalRead(button);

 boolean button2_old = digitalRead(button2);
 delay(10);
 boolean button2_new = digitalRead(button2);
 
 if(button_old && button_new == LOW){
  minutes++;
  }
 if(button2_old && button2_new == LOW){
  hours++;
 }
 if (minutes>9){//minute overflow
  minutes = 0;
  tens_minutes++;
  }
 if (tens_minutes>5){//tens of minutes overflow
  tens_minutes = 0;
  hours++;
  }
 if (hours>9){//hours overflow
  hours = 0;
  tens_hours++;
  }
 if (hours>3 && tens_hours==2){//tens of hours overflow
  tens_hours = 0;
  hours = 0;
  }
}
void display1(){
  PORTB = B00001000;//4th digit high
      PORTD = states[tens_hours];//Number in array represents numerals 0-9
      delay(1);
      PORTB = B00000100;//3rd digit high
      PORTD = states[hours];
      delay(1);
      PORTB = B00000010;//2nd digit high
      PORTD = states[tens_minutes];
      delay(1);
      PORTB = B00000001;//1st digit high
      PORTD = states[minutes];
      delay(1);
}
  
void loop(){
  display1();
  debounce();
}
  


