#pragma once
#include <string>
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>


class JniMqttBroker {
	public:
	 	explicit JniMqttBroker(const std::string& brokerIp, const int brokerPort);
		void setup();
		void loop();
	private:
	 	bool reconnect();
		void callback(char* topic, byte* payload, unsigned int length);

		std::string m_brokerIp;
		int m_brokerPort;
		PubSubClient m_client;
		long m_lastReconnectAttempt = 0;

};
