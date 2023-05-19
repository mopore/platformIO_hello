#include <Arduino.h>
#include "jni_wifi.h"
#include "jni_config.h"
#include "jni_mqtt_broker.h"

JniMqttBroker& broker = JniMqttBroker::getInstance();

void setup() {
	Serial.begin(115200);
	delay(10);
	
	char out_ip[MAX_IP_LENGTH];
	connect_wifi(out_ip, JNI_WIFI_SSID, JNI_WIFI_PASS);

	if (strcmp(out_ip, NO_IP) != 0) {
		Serial.printf("Connected with IP address: %s\n", out_ip);
	}
	else {
		Serial.println("Failed to connect to WiFi");
	}

	broker.setup(JNI_MQTT_BROKER_IP, JNI_MQTT_BROKER_PORT);
}


void loop() {
	broker.loop();
	delay(100); // Going with 10 Hz
}