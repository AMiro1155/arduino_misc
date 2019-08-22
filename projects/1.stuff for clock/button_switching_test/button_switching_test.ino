//Setting up array with segment values
byte states[10] = {0x80, 0xf2, 0x48, 0x60, 0x32, 0x24, 0x04, 0xf0, 0x00, 0x20};

//Values for digits
int minutes = 0;
int tens_minutes = 0;
int hours = 0;
int tens_hours = 0;
byte times[4] = {minutes, tens_minutes, hours, tens_hours};

boolean lastButt = LOW;
boolean currentButt = LOW;

int button = 14;
//Setting up registers
void setup(){
  DDRD = DDRD | B11111110;//setting up pins 7-1 as outputs
  DDRB = DDRB | B00001111;//setting up pins 8-11 as outputs
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
} 

boolean debounce(boolean lastButt){
   boolean current = digitalRead(button);
   if (lastButt = current){
     delay(5);
     current = !digitalRead(button);
  }
  return current;
}

void butt(){
  
  currentButt = debounce(lastButt);
  if (lastButt == LOW && currentButt == HIGH){
  minutes++;
  }
 lastButt = currentButt;
  
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
  PORTB = digits[dignum];//1st digit high
  PORTD = states[times[minutes]];
}
  
void loop(){
  display1();
  butt();
}
  


