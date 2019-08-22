//Setting up array with segment values
byte states[13] = {0x80, 0xf2, 0x48, 0x60, 0x32, 0x24, 0x04, 0xf0, 0x00, 0x20, 0x8c, 0x7e, 0xfe};
byte colon_state[3] = {0x00, 0x10, 0x08};
byte colon = 0x00;
byte minus_temp = 0x00;

//Timing values
#define max_Time_val 34359738//value for overflow of timer1
unsigned long oldTime = 0;
unsigned long newTime = 0;
unsigned long diffTime = 0;

//Values for clock
int seconds = 0;//units of seconds
int tens_seconds = 0;//tens of seconds
int minutes = 0;//units of minutes
int tens_minutes = 0;//tens of minutes
int hours = 0;//units of hours
int tens_hours = 0;//tens of hours

//Values for thermo
int degree = 0;//unit of temperature
int tens_degree = 0;//tens of temperature
float voltage = 0;//voltage output by sensor
int temper = 0;//temperature recorded by sensor
int calib_T = 0;//actual temperature
int minus = 12;//value for showing minus sign

//Pins
int button = 14;//digital pin 14 for first button input
int button2 = 15;//digital pin 15 for second button input

int time_set = 0;//value for getting out of while loop
boolean thermo_disp = LOW;//value for switching between clock and temp
boolean seco_disp = LOW;//value for switching between hours and seconds
//values for button function
unsigned long timer_start = 0;//start of timer
unsigned long timer_end = 0;//end of timer

boolean old_butt = LOW;//previous state of button1
boolean old_butt2 = LOW;//previous state of button2

boolean new_butt = HIGH;//state of button on pin 14
boolean new_butt2 = HIGH;//state of button on pin 15



void setup(){//setting up registers
  DDRD = DDRD | B11111110;//setting up pins 7-1 as outputs
  DDRB = DDRB | B00111111;//setting up pins 8-11 as outputs
  pinMode(button, INPUT);//button 1 as input
  pinMode(button2, INPUT);//button 2 as input
  digitalWrite(button, HIGH);//20k pullup activated
  digitalWrite(button2, HIGH);//same here
} 

//Clock function
void clock(){
  newTime = millis();
  if (newTime < oldTime){//if timer overflowed
    diffTime += max_Time_val - newTime + oldTime;
  }
  else {
    diffTime += newTime - oldTime;
  }
  if (diffTime>999){//if duration of about 1000ms passed add 1 to second
    seconds++;
    diffTime = diffTime-1000;
  }
  if (seconds>9){//second units overflow
    tens_seconds++;
    seconds = 0;
  }
  if(seconds%2 == 0){
    colon = colon_state[1];
  }
  else{
    colon = colon_state[0];
  }
  if (tens_seconds>5){//second tens overflow
    minutes++;
    tens_seconds = 0;
  }
  if (minutes>9){//minute units overflow
    tens_minutes++;
    minutes = 0;
  }
  if (tens_minutes>5){//minutes tens overflow
    hours++;
    tens_minutes = 0;
  }
  if (hours>9){//hours overflow
    tens_hours++;
    hours = 0;
  }
  if (tens_hours == 2 && hours == 4){//resets to 00:00:00 after 23:59:59
    tens_hours = 0;
    hours = 0;
  }
  oldTime = newTime;
}

//Display control function
void display1(){//Multiplexing display for clock

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
      PORTB = colon;//colon
      delayMicroseconds(500);
      PORTB = B00000000;//decrease brightness
      delayMicroseconds(500);
}

//Setting the time function
void setting_time(){
 new_butt = digitalRead(button2);//read state of pin 14
 new_butt2 = digitalRead(button);//read state of pin 15
 if(new_butt == LOW && old_butt == LOW){//button 1 press
  timer_start = millis();//value that will allow to calculate duration of button press/release
  old_butt = HIGH;
  }
  
 if(new_butt == HIGH && old_butt == HIGH){//button 1 release
  timer_end = millis();
  long timer_diff = timer_end - timer_start;
  if(timer_diff >= 1000){//if button held for longer than 1000ms (1s)
   old_butt = LOW;
   time_set++;;//continue to main clock program
  }
  else{
  minutes++;
  }
  old_butt = LOW;
  }
 
 if(new_butt2 == LOW && old_butt2 == LOW){//button 2 press
  old_butt2 = HIGH;
  }
 
 if(new_butt2 == HIGH && old_butt2 == HIGH){//button 2 release
  old_butt2 = LOW;
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

void temp(){//processing temp sensor and calculation of display digits
   temper = analogRead(5);//read adc value of analogue pin 5
   voltage = temper * 5.0;
   voltage /= 1023.0;//convert value to voltage
   int T = (voltage - 0.5) * 100;
   if(T>=0){
     colon = 0x00;//turn off minus
   }
   if(T<0){
     T = T + (T*(-2));
     colon = colon_state[2];//turn on minus
   }
   tens_degree = T/10;
   degree = T - (tens_degree *10);
   
}

void butt_thermo(){//function for getting into thermometer
 new_butt = digitalRead(button);
 if(new_butt == LOW && old_butt == LOW){//button 1 press
  old_butt = HIGH;
  }
  
 if(new_butt == HIGH && old_butt == HIGH){//button 1 release
  old_butt = LOW;
  thermo_disp = !thermo_disp;
 }
}

void display_temp(){//multiplexing display for temp
      PORTB = colon;//4th digit high, minus sign
      PORTD = states[11];
      delayMicroseconds(500);
      PORTB = B00000100;//3rd digit high
      PORTD = states[tens_degree];
      delayMicroseconds(500);
      PORTB = B00000010;//2nd digit high
      PORTD = states[degree];
      delayMicroseconds(500);
      PORTB = B00100000;//apostrophe
      delayMicroseconds(500);
      PORTB = B00000001;//C
      PORTD = states[10];
      delayMicroseconds(500);
      PORTB = B00000000;//brightness
      delayMicroseconds(500);
}

void temp_loop(){
  while(thermo_disp == HIGH){//loops until first button pressed
    temp();
    display_temp();
    butt_thermo();
  }
}

void butt_second(){
  new_butt2 = digitalRead(button2);
  if(new_butt2 == LOW && old_butt2 == LOW){//button 2 press
  old_butt2 = HIGH;
  }
  
  if(new_butt2 == HIGH && old_butt2 == HIGH){//button 2 release
  old_butt2 = LOW;
  seco_disp = !seco_disp;
 }
}

void second_loop(){
  while(seco_disp == HIGH){//loops until second button pressed
   clock();
   display2();
   butt_second();
   butt_thermo();
   temp_loop();
  }
}

void display2(){//Multiplexing display for clock (seconds)
      PORTB = B00001000;//4th digit high
      PORTD = states[tens_minutes];//Number in array represents numerals 0-9
      delayMicroseconds(500);
      PORTB = B00000100;//3rd digit high
      PORTD = states[minutes];
      delayMicroseconds(500);
      PORTB = B00000010;//2nd digit high
      PORTD = states[tens_seconds];
      delayMicroseconds(500);
      PORTB = B00000001;//1st digit high
      PORTD = states[seconds];
      delayMicroseconds(500);
      PORTB = B00010000;//colon
      delayMicroseconds(500);
      PORTB = B00000000;//decrease brightness
      delayMicroseconds(500);
}

void loop(){
 
  while(time_set != 1){//loops until button 2 is pressed for 1 second
    setting_time();
    display1();
  }
  clock();
  display1();
  butt_thermo();
  butt_second();
  temp_loop();
  second_loop(); 
}
