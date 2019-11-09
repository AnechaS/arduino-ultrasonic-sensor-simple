# Arduino Ultrasonic Sensor Simple
    
Sensor module to measure the distance 2cm to 400 cm

### Equipment used

* Ultrasonic HC-SR04
* NodeMCU  v2.0
* Breadboad
* Jumper wire

### Complete the circuit assembly as shown below.
![alt text](.github/esp-sr04.png)

### Code
```c
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
      digitalWrite(led, HIGH);                                             
      delay(300);  
      digitalWrite(led, LOW);  
      delay(300); 
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
```
