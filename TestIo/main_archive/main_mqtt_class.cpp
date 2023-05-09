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
	
	char out_ip[16];
	connect_wifi(out_ip, ssid, password);
	if (returned_ip == NO_IP) {
		Serial.println("Failed to connect to WiFi");
		return;
	}
	else {
		Serial.printf("Connected with IP address: %s\n", returned_ip);
	}

	broker.setup(JNI_MQTT_BROKER_IP, JNI_MQTT_BROKER_PORT);
}


void loop() {
	broker.loop();
	delay(100); // Goging with 10 Hz
}