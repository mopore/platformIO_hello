#include <Arduino.h>
#include <memory>
#include "jni_mqtt_broker.h"

JniMqttBroker* JniMqttBroker::s_instance = nullptr;

JniMqttBroker& JniMqttBroker::getInstance(const std::string& brokerIp, const int brokerPort) {
	static JniMqttBroker instance(brokerIp, brokerPort);
	return instance;
}

// Private constructor...
JniMqttBroker::JniMqttBroker(const std::string& brokerIp, const int brokerPort) : 
	_brokerIp(brokerIp),
	_brokerPort(1883) {

	WiFiClient espClient;
	PubSubClient client(espClient);
	this->_client = client;
	s_instance = this;
}


void JniMqttBroker::setup() {
	this->_client.setServer(this->_brokerIp.c_str(), this->_brokerPort);
	this->_client.setCallback(JniMqttBroker::onMessage);
	delay(1500);
	this->_lastReconnectAttempt = 0;
}


void JniMqttBroker::loop() {
	if (!this->_client.connected()) {
		long now = millis();
		if (now - this->_lastReconnectAttempt > 5000) {
			this->_lastReconnectAttempt = now;
			// Attempt to reconnect
			if (this->_reconnect()) {
				this->_lastReconnectAttempt = 0;
			}
		}
	} else {
		// Client connected
		this->_client.loop();  // Non-blocking function for client
	}
}


// Static method to pass messages to instance
void JniMqttBroker::onMessage(char* topic, byte* payload, unsigned int length) {
	if (s_instance != nullptr){
		s_instance->_handleMessage(topic, payload, length);
	}
} 


void JniMqttBroker::_handleMessage(char* topic, byte* payload, unsigned int length){
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


boolean JniMqttBroker::_reconnect() {
	if (this->_client.connect("arduinoClient")) {
		// Once connected, publish an announcement...
		this->_client.publish("outTopic","hello world");
		// ... and subscribe to a topic...
		this->_client.subscribe("inTopic");
	}
	return this->_client.connected();
}