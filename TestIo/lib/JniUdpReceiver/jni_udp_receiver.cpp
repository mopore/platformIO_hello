#include <Arduino.h>
#include <AsyncUDP.h>
// #include <esp_wifi.h>
#include "jni_udp_receiver.h"



JniUdpReceiver::JniUdpReceiver() {
	packetsCounter = 0;
	loopCounter = 0;
}

void JniUdpReceiver::setup() {
	byte packetBuffer[UDP_RECEIVER_PACKAGE_SIZE];
	if (udp.listen(UDP_RECEIVER_SOCKET_PORT)) {
		Serial.println("Listening...");
		// Aysnchronously receive UDP packets
		udp.onPacket([this](AsyncUDPPacket packet) {
			if (packet.length() == UDP_RECEIVER_PACKAGE_SIZE) {
				int16_t x = packet.data()[0] | packet.data()[1] << 8;
				int16_t y = packet.data()[2] | packet.data()[3] << 8;
				packetsCounter++;
			}
			
		});
	}
}


void JniUdpReceiver::loop() {
	
	// This loop only prints the packets/s
	delay(1000);
	loopCounter++;
	// Serial.printf("My IP: %d.%d.%d.%d\n", ipAddress[0], ipAddress[1], ipAddress[2], ipAddress[3]);
	Serial.printf("Tick... #%d packets/s: %d\n", loopCounter, packetsCounter);
	if (packetsCounter > 0) {
		digitalWrite(LED_BUILTIN, HIGH);
	}
	else {
		digitalWrite(LED_BUILTIN, LOW);
	}
	packetsCounter = 0;
}
