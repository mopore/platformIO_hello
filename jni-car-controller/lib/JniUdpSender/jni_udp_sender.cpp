#include "jni_udp_sender.h"

#define UDP_RECEIVER_SOCKET_IP "192.168.199.245"
#define UDP_RECEIVER_SOCKET_PORT 8080
#define UDP_RECEIVER_PACKAGE_SIZE 4	


JniUdpSender::JniUdpSender() {
}


void JniUdpSender::setup() {
	m_udp.begin(UDP_RECEIVER_SOCKET_PORT);

}


void JniUdpSender::send(int16_t x, int16_t y){
        byte packetBuffer[4];
        packetBuffer[0] = x & 0xFF;
        packetBuffer[1] = (x >> 8) & 0xFF;
        packetBuffer[2] = y & 0xFF;
        packetBuffer[3] = (y >> 8) & 0xFF;

		m_udp.beginPacket(UDP_RECEIVER_SOCKET_IP, UDP_RECEIVER_SOCKET_PORT);
		m_udp.write(packetBuffer, 4);
		m_udp.endPacket();
}