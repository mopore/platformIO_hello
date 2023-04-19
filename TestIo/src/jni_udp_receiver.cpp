#include <AsyncUDP.h>
#include <Arduino.h>
#include "jni_udp_receiver.h"


JniUdpReceiver::JniUdpReceiver() {
	packetsCounter = 0;
}

void JniUdpReceiver::setup() {
	byte packetBuffer[UDP_RECEIVER_PACKAGE_SIZE];
	if (udp.listen(UDP_RECEIVER_SOCKET_PORT)) {
		Serial.println("Listening...");
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
