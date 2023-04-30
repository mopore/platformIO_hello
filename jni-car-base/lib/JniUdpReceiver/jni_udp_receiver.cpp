#include "jni_udp_receiver.h"


JniUdpReceiver::JniUdpReceiver() {
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
				carInput.x = x;
				carInput.y = y;
			}
		});
	}
}
