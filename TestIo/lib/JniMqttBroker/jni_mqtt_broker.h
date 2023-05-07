#pragma once
#include <string>
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>


class JniMqttBroker {
	public:
	 	static JniMqttBroker& getInstance(const std::string& brokerIp, const int brokerPort);
		static void onMessage(char* topic, byte* payload, unsigned int length);

		void setup();
		void loop();

	private:
	 	explicit JniMqttBroker(const std::string& brokerIp, const int brokerPort);
	 	bool _reconnect();
		void _handleMessage(char* topic, byte* payload, unsigned int length);

		static JniMqttBroker* s_instance;
		std::string _brokerIp;
		int _brokerPort;
		PubSubClient _client;
		long _lastReconnectAttempt = 0;


};
