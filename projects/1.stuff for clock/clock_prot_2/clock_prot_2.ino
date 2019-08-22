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





//Pins
int button = 14;//digital pin 14 for first button input
int button2 = 15;//digital pin 15 for second button input

int time_set = 0;//value for getting out of while loop

//values for button function
unsigned long timer_start = 0;//start of timer
unsigned long timer_end = 0;//end of timer

boolean old_butt = LOW;//previous state of button1
boolean old_butt2 = LOW;//previous state of button2

boolean new_butt = digitalRead(button2);
boolean new_butt2 = digitalRead(button);


//Setting up registers
void setup(){
  DDRD = DDRD | B11111110;//setting up pins 7-1 as outputs
  DDRB = DDRB | B00111111;//setting up pins 8-11 as outputs
  pinMode(button, INPUT);
  pinMode(button2, INPUT);
  digitalWrite(button, HIGH);
  digitalWrite(button2, HIGH);
  
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
  if (tens_hours == 2 && hours == 4){
    tens_hours = 0;
    hours = 0;
  }
  oldTime = newTime;
}

//Display control function
void display1(){//multiplexed display function

      PORTB = B00001000;//4th digit high
      PORTD = states[tens_hours];//Number in array represents numerals 0-9
      delayMicroseconds(500);
      PORTB = B00000100;//3rd digit high
      PORTD = states[hours];
      delayMicroseconds(500);
      PORTB = B00000010;//2nd digit high
      PORTD = states[tens_minutes];
      delayMicroseconds(500);
      PORTB = B00000001;//1st digit high
      PORTD = states[minutes];
      delayMicroseconds(500);
      PORTB = B00010000;//colon
      delayMicroseconds(500);
      PORTB = B00100000;//apostro
      delayMicroseconds(500);
      PORTB = B00000000;//decrease brightness
      delayMicroseconds(500);
}

//Setting the time function
void setting_time(){
 boolean new_butt = digitalRead(button2);
 boolean new_butt2 = digitalRead(button);
 if(new_butt == LOW && old_butt == LOW){//button 1 press
  timer_start = millis();
  old_butt = HIGH;
  }
  
 if(new_butt == HIGH && old_butt == HIGH){//button 1 release
  timer_end = millis();
  long timer_diff = timer_end - timer_start;
  if(timer_diff >= 1000){
   time_set++;;
  }
  else{
  minutes++;
  }
  old_butt = LOW;
  }
 
 if(new_butt2 == LOW && old_butt2 == LOW){//button 2 press
  hours++;
  old_butt2 = HIGH;
  }
 
 if(new_butt2 == HIGH && old_butt2 == HIGH){//button 2 release
  old_butt2 = LOW;
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

void loop(){
 
  while(time_set != 1){//loops until both buttons pressed
    setting_time();
    display1();
  }
    clock();
    display1();
}
