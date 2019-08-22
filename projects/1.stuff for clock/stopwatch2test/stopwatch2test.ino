//Setting up array with segment values
byte states[10] = {0x80, 0xf2, 0x48, 0x60, 0x32, 0x24, 0x04, 0xf0, 0x00, 0x20};

//Timing values
#define max_Time_val 34359738
unsigned long oldTime, newTime, diffTime;

//Values for digits
int seconds = 0;
int tens_seconds = 0;
int minutes = 0;
int tens_minutes = 0;

//Pins
int button = 14;
int button2 = 15;

boolean val = LOW;
boolean new_butt = 0;
boolean old_butt = LOW;


//Setting up registers
void setup(){
  DDRD = DDRD | B11111110;//setting up pins 7-1 as outputs
  DDRB = DDRB | B00001111;//setting up pins 8-11 as outputs
  pinMode(button, INPUT);
  pinMode(button2, INPUT);
  digitalWrite(button, HIGH);
  digitalWrite(button2, HIGH);
  
} 

//Clock function
void clock(){
 if (val == LOW){
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
  if (seconds>9){
    tens_seconds++;
    seconds = 0;
  }
  if (tens_seconds>5){
    minutes++;
    tens_seconds = 0;
  }
  if (minutes>9){
    tens_minutes++;
    minutes = 0;
  }
  if (tens_minutes>5){
    tens_minutes = 0;
  }
  oldTime = newTime;
 }
}

//Display control function
void display1(){
      PORTB = B00001000;//4th digit high
      PORTD = states[tens_minutes];//Number in array represents numerals 0-9
      delay(1);
      PORTB = B00000100;//3rd digit high
      PORTD = states[minutes];
      delay(1);
      PORTB = B00000010;//2nd digit high
      PORTD = states[tens_seconds];
      delay(1);
      PORTB = B00000001;//1st digit high
      PORTD = states[seconds];
      delay(1);
      PORTB = B00000000;//decrease brightness
      delay(1);
}

//Setting the time function
void butt(){
 new_butt = digitalRead(button);
 
 if(new_butt == LOW && old_butt == LOW){
   old_butt = HIGH;
   val = !val;
  }
  
 if(new_butt == HIGH && old_butt == HIGH){
  old_butt = LOW;
  oldTime = newTime;
 }
}

void loop(){
    butt();
    clock();
    display1();
}
