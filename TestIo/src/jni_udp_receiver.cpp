#include <AsyncUDP.h>
#include <Arduino.h>
#include "jni_udp_receiver.h"

const uint16_t SOCKET_PORT = 8080;
const int PACKAGE_SIZE = 4;
AsyncUDP udp;
int packetsCounter = 0;

JniUdpReceiver::JniUdpReceiver() {
}

void JniUdpReceiver::setup() {
	byte packetBuffer[PACKAGE_SIZE];
	if (udp.listen(SOCKET_PORT)) {
		Serial.println("Listening...");
		udp.onPacket([](AsyncUDPPacket packet) {
			if (packet.length() == PACKAGE_SIZE) {
				int16_t x = packet.data()[0] | packet.data()[1] << 8;
				int16_t y = packet.data()[2] | packet.data()[3] << 8;
				packetsCounter++;
			}
			
		});
	}
}


void JniUdpReceiver::loop() {
	delay(1000);
	Serial.printf("packets/s: %d\n", packetsCounter);
	if (packetsCounter > 0) {
		digitalWrite(LED_BUILTIN, HIGH);
	}
	else {
		digitalWrite(LED_BUILTIN, LOW);
	}
	packetsCounter = 0;
}
