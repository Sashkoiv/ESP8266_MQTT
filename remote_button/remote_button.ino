#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "the ssid";
const char* password = "the password";

const int buttonPin = 0;
const int ledPin = 2;

IPAddress mqtt_server(192, 168, 31, 133);

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);

    pinMode(buttonPin, INPUT);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);
}

void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    //WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i=0;i<length;i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void ERR_blink () {
    digitalWrite(ledPin, LOW);
    delay(100);
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
    digitalWrite(ledPin, HIGH);
}

void SUCC_blink () {
    digitalWrite(ledPin, LOW);
    delay(500);
    digitalWrite(ledPin, HIGH);
}

void loop()
{
    if (client.connect("espbutton001")) {
        if (digitalRead(0)==LOW) {
            client.publish("test", "the button is pressed");
            client.subscribe("esp");
            SUCC_blink();
        } else {
            //An action when the button is not pressed
        }
    } else {
        Serial.println("Not connected");
        ERR_blink();
    }

    delay(100);
    client.loop();
}
