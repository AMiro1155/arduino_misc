//Setting up array with segment values
byte states[10] = {0x80, 0xf2, 0x48, 0x60, 0x32, 0x24, 0x04, 0xf0, 0x00, 0x20};

//Timing values
#define max_Time_val 34359738
unsigned long oldTime = 0;
unsigned long newTime = 0;
unsigned long diffTime = 0;

//Values for digits
int seconds = 0;
int minutes = 0;
int tens_minutes = 0;
int hours = 0;
int tens_hours = 0;

//boolean stuff
boolean lastButt = LOW;
boolean currentButt = LOW;

//Pins
int button = 14;

//Setting up registers
void setup(){
  DDRD = DDRD | B11111110;//setting up pins 7-1 as outputs
  DDRB = DDRB | B00001111;//setting up pins 8-11 as outputs
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
} 

//button debouncing
boolean debounce(boolean lastButt){
   boolean current = digitalRead(button);
   if (lastButt = current){
     delay(5);
     current = !digitalRead(button);
  }
  return current;
}

//Clock function
void clock(){
  newTime = millis();
  if (newTime < oldTime){
    diffTime += max_Time_val - newTime + oldTime;
  }
  else {
    diffTime += newTime - oldTime;
  }
  if (diffTime>999){
    seconds++;
    diffTime = diffTime-1000;
  }
  if (seconds>59){
    minutes++;
    seconds = 0;
  }
  if (minutes>9){
    tens_minutes++;
    minutes = 0;
  }
  if (tens_minutes>5){
    hours++;
    tens_minutes = 0;
  }
  if (hours>9){
    tens_hours++;
    hours = 0;
  }
  if (tens_hours>2){
    tens_hours = 0;
  }
  oldTime = newTime;
}

//Display control function
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

//Setting the time function
void setting_time(){
 currentButt = debounce(lastButt);
 if (lastButt == LOW && currentButt == HIGH){
  minutes++;
  }
 lastButt = currentButt;
}

void loop(){
    setting_time();
    clock();
    display1();
}
