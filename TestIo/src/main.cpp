#include <Arduino.h>
#include <string>
#include <SPI.h>
#include <PubSubClient.h>
#include "WiFi.h"
#include "jni_wifi.h"

// Update these with values suitable for your hardware/network.
IPAddress server(192, 168, 199, 119);

void callback(char* topic, byte* payload, unsigned int length) {
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

WiFiClient espClient;
PubSubClient client(espClient);

long lastReconnectAttempt = 0;

boolean reconnect() {
	if (client.connect("arduinoClient")) {
		// Once connected, publish an announcement...
		client.publish("outTopic","hello world");
		// ... and subscribe to a topic...
		client.subscribe("inTopic");
	}
	return client.connected();
}

void setup() {
	Serial.begin(115200);
	delay(10);
	const std::string ssid = "Loxodonta";
	const std::string password = "Twitch7%Carton%Driller%Bluish";
	
	auto returned_ip = connect_wifi(ssid, password).c_str();
	if (returned_ip == NO_IP) {
		Serial.println("Failed to connect to WiFi");
		return;
	}
	else {
		Serial.printf("Connected with IP address: %s\n", returned_ip);
	}

	client.setServer(server, 1883);
	client.setCallback(callback);
	delay(1500);
	lastReconnectAttempt = 0;
}


void loop()
{
	if (!client.connected()) {
		long now = millis();
		if (now - lastReconnectAttempt > 5000) {
			lastReconnectAttempt = now;
			// Attempt to reconnect
			if (reconnect()) {
				lastReconnectAttempt = 0;
			}
		}
	} else {
		// Client connected
		client.loop();  // Non-blocking function for client
	}

}