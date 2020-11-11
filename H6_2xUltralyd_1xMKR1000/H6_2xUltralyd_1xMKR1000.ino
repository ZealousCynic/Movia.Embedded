#define echoPin1 0 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin1 1 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin2 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin2 3 //attach pin D3 Arduino to pin Trig of HC-SR04
int counter = 0; //counter for ppl inside the bus

// defines variables
long duration1; // variable for the duration of sound wave travel
int distance1; // variable for the distance measurement
long duration2; // variable for the duration of sound wave travel
int distance2; // variable for the distance measurement

int currentState = 0;
int previousState = 0;
int currentState2 = 0;
int previousState2 = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin1, INPUT); // Sets the echoPin as an INPUT 
  
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin as an INPUT
  
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  while(!Serial); // Await Serial
  
  Serial.println("Ultrasonic Sensor HC-SR04"); // print some text in Serial Monitor
  Serial.println("With MKR1000");
}

void loop() {
  // put your main code here, to run repeatedly:
  currentState = 0;
  currentState2 = 0;  
  
  Serial.println(" ");
  Serial.print("Counter: ");
  Serial.print(counter);
  Serial.println(" ");

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

   
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  Serial.print("Distance sensor 1: ");
  Serial.print(distance1);
  Serial.println(" cm");
 
  Serial.print("Distance sensor 2: ");
  Serial.print(distance2);
  Serial.println(" cm");
  Serial.println(" ");
  
 if (distance1 <= 15){
 currentState = 1;
 }
 else {
 currentState = 0;
 }
 if(currentState != previousState){
  while(currentState == 1) {
  digitalWrite(trigPin2, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;
  if (distance2 <= 15){
 currentState2 = 1;
 }
 else {
 currentState2 = 0;
 }
 if(currentState2 != previousState2){
 if(currentState2 == 1) {
  counter = counter+1;
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
 digitalWrite(trigPin1, LOW); 
 delayMicroseconds(2); 
 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10); 
 digitalWrite(trigPin1, LOW);
 duration1 = pulseIn(echoPin1, HIGH);
 distance1 = duration1 * 0.034 / 2;
 if (distance1 <= 15){
 currentState = 1;
 }
 else {
 currentState = 0;
 }
  if(currentState != previousState){
  if(currentState == 1 && counter != 0) {
   counter = counter-1;
   
   delay(400); // pause for 1/2 second
  }
   return;
   }
  }
 }
}
