#pragma once
#include <string>
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>  // knolleary/PubSubClient@^2.8


class JniMqttBroker {
	public:
	 	static JniMqttBroker& getInstance();
		static void onMessage(char* topic, byte* payload, unsigned int length);

		void setup(const std::string& brokerIp, const int brokerPort);
		void loop();

	private:
	 	explicit JniMqttBroker();
	 	bool _reconnect();
		void _handleMessage(char* topic, byte* payload, unsigned int length);

		static JniMqttBroker s_instance;
		WiFiClient _espClient;
		PubSubClient _client;
		long _lastReconnectAttempt = 0;


};
