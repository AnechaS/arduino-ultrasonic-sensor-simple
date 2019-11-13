#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid     = "YOU_WIFI_NAME";
const char* password = "YOU_WIFI_PASSWORD";

// set config netpie https://netpie.io/
#define APPID   "YOU_NETPIE_APP_ID" 
#define KEY     "YOU_NETPIE_APP_KEY"
#define SECRET  "YOU_NETPIE_APP_SECRET"

// set unique name
#define UNAME   "switch"

#define TRIGGER_PIN  5
#define ECHO_PIN     4

// pin led zx-led
const int led = 13;

WiFiClient client;

MicroGear microgear(client);

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    microgear.setName(UNAME);
}

void setup() {  
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(led, OUTPUT); 
  pinMode(D1,OUTPUT);

  microgear.on(CONNECTED,onConnected);

  Serial.begin(115200);
  Serial.println("Starting...");

  pinMode(LED_BUILTIN, OUTPUT);

  if (WiFi.begin(ssid, password)) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
        Serial.print(".");
      }
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  microgear.init(KEY,SECRET,UNAME);
  microgear.connect(APPID);  
}

void loop() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long duration, distance;
  duration = pulseIn(ECHO_PIN, HIGH);
  distance =  duration * 0.034 / 2;
  
  Serial.print(distance);
  Serial.println(" cm");
    
  if(distance <= 6) {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(led, HIGH);                                             
    delay(200);  
    digitalWrite(led, LOW);  
    delay(200); 
      
    Serial.println("pieled 1");

    // send to thing name pieled to on led
    microgear.chat("pieled","1");
   
  } else if(distance <= 10 && distance > 6) {
    digitalWrite(LED_BUILTIN, LOW); 
    // delay(400);                                              
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(led, LOW); 

    Serial.println("pieled 0");

    // send to thing name pieled to off led
    microgear.chat("pieled","0");
    // delay(400);  
  }
}
