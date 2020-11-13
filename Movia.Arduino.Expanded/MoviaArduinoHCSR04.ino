void getUltrasoundReading() {

  currentState = 0;
  currentState2 = 0;  
  
  digitalWrite(TRIGPIN_1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN_1, LOW);
  duration1 = pulseIn(ECHOPIN_1, HIGH);
  distance1 = duration1 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

   
  digitalWrite(TRIGPIN_2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN_2, LOW);
  duration2 = pulseIn(ECHOPIN_2, HIGH);
  distance2 = duration2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
 if (distance1 <= 15){
 currentState = 1;
 }
 else {
 currentState = 0;
 }
 if(currentState != previousState){
  while(currentState == 1) {
  digitalWrite(TRIGPIN_2, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIGPIN_2, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGPIN_2, LOW);
  duration2 = pulseIn(ECHOPIN_2, HIGH);
  distance2 = duration2 * 0.034 / 2;
  if (distance2 <= 15){
 currentState2 = 1;
 }
 else {
 currentState2 = 0;
 }
 if(currentState2 != previousState2){
 if(currentState2 == 1) {
  wifiHCSR04Routine("increase");
  delay(400); // pause for 1/2 second
 }
 return;
   }
  }
 }
 if (distance2 <= 15){
 currentState2 = 1;
 }
 else {
 currentState2 = 0;
 }
 if(currentState2 != previousState2){
 while (currentState2 == 1) {
 digitalWrite(TRIGPIN_1, LOW); 
 delayMicroseconds(2); 
 digitalWrite(TRIGPIN_1, HIGH);
 delayMicroseconds(10); 
 digitalWrite(TRIGPIN_1, LOW);
 duration1 = pulseIn(ECHOPIN_1, HIGH);
 distance1 = duration1 * 0.034 / 2;
 if (distance1 <= 15){
 currentState = 1;
 }
 else {
 currentState = 0;
 }
  if(currentState != previousState){
  if(currentState == 1) {
   wifiHCSR04Routine("decrease");
   
   delay(400); // pause for 1/2 second
  }
   return;
   }
  }
 }
}
