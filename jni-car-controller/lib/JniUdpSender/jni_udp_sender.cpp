#include "jni_udp_sender.h"

#define UDP_RECEIVER_PACKAGE_SIZE 4	


JniUdpSender::JniUdpSender(
    const std::string& udp_target_ip,
    const uint16_t udp_target_port
):
    m_udp_target_ip(udp_target_ip),
    m_udp_target_port(udp_target_port){
}


void JniUdpSender::setup() {
	m_udp.begin(m_udp_target_port);

}


void JniUdpSender::send(int16_t x, int16_t y){
        byte packetBuffer[4];
        packetBuffer[0] = x & 0xFF;
        packetBuffer[1] = (x >> 8) & 0xFF;
        packetBuffer[2] = y & 0xFF;
        packetBuffer[3] = (y >> 8) & 0xFF;

		m_udp.beginPacket(m_udp_target_ip.c_str(), m_udp_target_port);
		m_udp.write(packetBuffer, 4);
		m_udp.endPacket();
}