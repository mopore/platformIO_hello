#include <Arduino.h>
#include <WiFi.h>
#include "jni_functions.h"


const char* WIFI_SSID = "Loxodonta";
const char* WIFI_PASS =  "Twitch7%Carton%Driller%Bluish";

const char * SOCKERT_SERVER = "192.168.199.245";
const uint16_t SOCKET_PORT = 8080;

const int HOLD_CONNECTION_TIME = 6000;
const int FREQ = 100;

boolean led_high = false; 

int16_t x = -100;
int16_t y = 0;

void sendLittleEndian(int16_t x, int16_t y, WiFiClient client) {
    uint8_t coord[4] = {static_cast<uint8_t>(x & 0xFF), static_cast<uint8_t>((x >> 8) & 0xFF),
                        static_cast<uint8_t>(y & 0xFF), static_cast<uint8_t>((y >> 8) & 0xFF)};
    client.write(coord, sizeof(coord));
    Serial.print("Sent coordinates: x = ");
    Serial.print(x);
    Serial.print(", y = ");
    Serial.println(y);
}

void connectToWiFi() {
	WiFi.begin(WIFI_SSID, WIFI_PASS);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}


void setup() {
	Serial.begin(115200);

	Person p("John", 30);
	Serial.println(p.toString());

	pinMode(LED_BUILTIN, OUTPUT);

	connectToWiFi();
	digitalWrite(LED_BUILTIN, HIGH);	
}

void loop() {
	jniFunction();

	WiFiClient client;

	if (!client.connect(SOCKERT_SERVER, SOCKET_PORT)) {
		Serial.println("Connection failed. Will try again in 5 seconds...");
		delay(5000);
		return;
	}

	Serial.println("Connected to server");
	ulong start = millis();
	ulong time_in_connection = millis() - start;
	ulong last_sent = 0;
	while (time_in_connection < HOLD_CONNECTION_TIME) {
		ulong now = millis();
		ulong time_after_last_sent = now - last_sent;
		if (time_after_last_sent > FREQ) {
			x++;
			y++;
			if (x > 100) {
				x = -100;
			}
			if (y > 100) {
				y = -100;
			}		
			digitalWrite(LED_BUILTIN, HIGH);
			sendLittleEndian(x, y, client);											
			last_sent = now;
		}
		time_in_connection = millis() - start;
	}
	client.stop();
	Serial.println("Connection closed");

	Serial.println("Pausing for 10 seconds...");
	digitalWrite(LED_BUILTIN, LOW);
	delay(10000);
}