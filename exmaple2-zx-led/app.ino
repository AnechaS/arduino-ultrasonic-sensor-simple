#define TRIGGER_PIN  5
#define ECHO_PIN     4

// pin zx-led 
// zx-led image https://inex.co.th/shop/media/catalog/product/cache/1/image/9df78eab33525d08d6e5fb8d27136e95/z/x/zx_led_r_1.jpg
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
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
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
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(led, LOW); 
  }
}
