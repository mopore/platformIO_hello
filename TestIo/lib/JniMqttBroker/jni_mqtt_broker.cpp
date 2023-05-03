#include <Arduino.h>
#include "jni_mqtt_broker.h"


JniMqttBroker::JniMqttBroker(const std::string& brokerIp, const int brokerPort) : 
	m_brokerIp(brokerIp),
	m_brokerPort(1883) {

	WiFiClient espClient;
	PubSubClient client(espClient);
	this->m_client = client;
}

void JniMqttBroker::setup() {
	this->m_client.setServer(this->m_brokerIp.c_str(), this->m_brokerPort);
	this->m_client.setCallback(callback);
	delay(1500);
	this->m_lastReconnectAttempt = 0;
}


void JniMqttBroker::loop() {
	if (!this->m_client.connected()) {
		long now = millis();
		if (now - this->m_lastReconnectAttempt > 5000) {
			this->m_lastReconnectAttempt = now;
			// Attempt to reconnect
			if (this->reconnect()) {
				this->m_lastReconnectAttempt = 0;
			}
		}
	} else {
		// Client connected
		this->m_client.loop();  // Non-blocking function for client
	}
}

void JniMqttBroker::callback(char* topic, byte* payload, unsigned int length){

	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	
	// Convert payload to string
	std::string payload_str;
	for (int i = 0; i < length; i++) {
		payload_str += (char)payload[i];
	}

	Serial.println(payload_str.c_str());
}


boolean JniMqttBroker::reconnect() {
	if (this->m_client.connect("arduinoClient")) {
		// Once connected, publish an announcement...
		this->m_client.publish("outTopic","hello world");
		// ... and subscribe to a topic...
		this->m_client.subscribe("inTopic");
	}
	return this->m_client.connected();
}