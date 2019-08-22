void setup(){
  pinMode(button, INPUT);
  pinMode(button2, INPUT);
  digitalWrite(button, HIGH);
  digitalWrite(button2, HIGH);
}
//Setting the time function
void setting_time(){
  int butt_state = 0;
  int butt_state2 = 0;
  int butt_dur = 0;
  int dignum = 0;
  byte times[4] = {minutes, tens_minutes, hours, tens_hours};
  
if (butt_dur < 5){
  butt_state = digitalRead(button);
  if (butt_state == LOW){
    times[dignum]++;
  }
  else {
    butt_state2 = digitalRead(button2);
    if (butt_state2 == LOW){
      dignum++;
      butt_dur++;
   }
  }
 }
}
