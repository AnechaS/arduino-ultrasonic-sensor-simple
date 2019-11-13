#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid     = "YOU_WIFI_NAME";
const char* password = "YOU_WIFI_PASSWORD";

// set config netpie https://netpie.io/
#define APPID   "YOU_NETPIE_APP_ID" 
#define KEY     "YOU_NETPIE_APP_KEY"
#define SECRET  "YOU_NETPIE_APP_SECRET"

// set unique name
#define UNAME   "pieled"

#define TRIGGER_PIN  5
#define ECHO_PIN     4

WiFiClient client;

int timer = 0;
MicroGear microgear(client);

// event receive message
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
    if(*(char *)msg == '1'){
        digitalWrite(LED_BUILTIN, LOW);   // LED on
        microgear.chat("switch","1");
    }else{
        digitalWrite(LED_BUILTIN, HIGH);  // LED off
        microgear.chat("switch","0");
    }
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    microgear.setName(UNAME);
}


const int led = 13;

void setup() {
    microgear.on(MESSAGE,onMsghandler);
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
    if (microgear.connected()) {
        Serial.println("..."); 
        microgear.loop();
        timer = 0;
    }
    else {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) {
            microgear.connect(APPID); 
            timer = 0;
        }
        else timer += 100;
    }
    delay(100);
}
