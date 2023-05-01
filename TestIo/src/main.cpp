#include <Arduino.h>
#include <string>
#include "jni_wifi.h"


void setup() {
	Serial.begin(115200);
	const std::string ssid = "Loxodonta";
	const std::string password = "Twitch7%Carton%Driller%Bluish";
	
	auto returned_ip = connect_wifi(ssid, password).c_str();
	if (returned_ip == NO_IP) {
		Serial.println("Failed to connect to WiFi");
		return;
	}
	else {
		Serial.printf("Connected with IP address: %s\n", returned_ip);
	}
}


void loop() {
	delay(100);
}