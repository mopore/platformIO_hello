#include <Arduino.h>
#include <string>
#include <SPI.h>
#include <PubSubClient.h>
#include "WiFi.h"
#include "jni_config.h"
#include "jni_wifi.h"
#include "jni_mqtt_broker.h"


JniMqttBroker mqtt_broker(JNI_MQTT_BROKER_IP, JNI_MQTT_BROKER_PORT);

void connectWifi() {
	auto returned_ip = connect_wifi(JNI_WIFI_SSID, JNI_WIFI_PASS).c_str();
	if (returned_ip == NO_IP) {
		Serial.println("Failed to connect to WiFi");
		throw ERR_NO_WIFI;
	}
	else {
		Serial.printf("Connected with IP address: %s\n", returned_ip);
	}
}


void setup() {
	Serial.begin(115200);
	delay(10);
	connectWifi();	

	mqtt_broker.setup();
}


void loop() {
	mqtt_broker.loop();
}