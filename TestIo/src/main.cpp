#include <Arduino.h>
#include <string>
#include <SPI.h>
#include "WiFi.h"
#include "jni_wifi.h"
#include "jni_config.h"
#include "jni_mqtt_broker.h"

JniMqttBroker broker = JniMqttBroker::getInstance();

void setup() {
	Serial.begin(115200);
	delay(10);
	
	const char* ssid = "Loxodonta";
	const char* password = "Twitch7%Carton%Driller%Bluish";
	
	char out_ip[16];
	connect_wifi(out_ip, ssid, password);

	if (strcmp(out_ip, NO_IP)) {
		Serial.printf("Connected with IP address: %s\n", out_ip);
	}
	else {
		Serial.println("Failed to connect to WiFi");
	}

	broker.setup(JNI_MQTT_BROKER_IP, JNI_MQTT_BROKER_PORT);
}


void loop() {
	broker.loop();
	delay(100); // Goging with 10 Hz
}