#define TRIGGER_PIN  5
#define ECHO_PIN     4

const int led = 13;

void setup() {  
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(led, OUTPUT); 
  pinMode(D1,OUTPUT);
  
  Serial.begin (9600);
}

void loop() {
  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance =  duration * 0.034 / 2;
  
  Serial.print(distance);
  Serial.println(" cm");
    
  if(distance <= 6) {
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(led, HIGH);                                             
      delay(100);  
      digitalWrite(led, LOW);  
      delay(100); 
  } else if(distance <= 10 && distance > 6) {
      digitalWrite(LED_BUILTIN, LOW);                                              
//      delay(300);  
//      digitalWrite(LED_BUILTIN, HIGH); 
//      delay(300); 
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(led, LOW); 
  }
}
