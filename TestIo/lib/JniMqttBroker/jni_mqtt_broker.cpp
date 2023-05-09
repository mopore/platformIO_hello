#include <Arduino.h>
#include "jni_mqtt_broker.h"

JniMqttBroker JniMqttBroker::s_instance;


JniMqttBroker& JniMqttBroker::getInstance() {
	return JniMqttBroker::s_instance;
}


// Private constructor...
JniMqttBroker::JniMqttBroker() :
	_espClient(),
	_client(_espClient) {
}


void JniMqttBroker::setup(const char* brokerIp, const int brokerPort) {
	_client.setServer(brokerIp, brokerPort);
	_client.setCallback(JniMqttBroker::onMessage);
	delay(1500);
	_lastReconnectAttempt = 0;
}


void JniMqttBroker::loop() {
	bool connected = _client.connected();
	if (!connected) {
		long now = millis();
		if (now - _lastReconnectAttempt > 5000) {
			_lastReconnectAttempt = now;
			// Attempt to reconnect
			if (_reconnect()) {
				_lastReconnectAttempt = 0;
			}
		}
	} else {
		// Client connected
		_client.loop();  // Non-blocking function for client
	}
}


// Static method to pass messages to instance
void JniMqttBroker::onMessage(char* topic, byte* payload, unsigned int length) {
	s_instance._handleMessage(topic, payload, length);
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
	Serial.println("Attempting MQTT connection...");
	if (_client.connect("arduinoClient")) {
		Serial.println("Connected to MQTT broker");
		_client.publish("outTopic","hello world");
		_client.subscribe("inTopic");
	}
	else {
		Serial.print("Failed, rc=");
		Serial.print(_client.state());
		Serial.println(" try again in 5 seconds");
	}
	return _client.connected();
}