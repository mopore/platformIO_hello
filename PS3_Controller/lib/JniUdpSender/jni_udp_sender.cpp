#include "jni_udp_sender.h"

#define PACKET_BUFFER_SIZE 4	


JniUdpSender::JniUdpSender(
    const char* udp_target_ip,
    const uint16_t udp_target_port
):
    m_udp_target_ip(udp_target_ip),
    m_udp_target_port(udp_target_port){
}


void JniUdpSender::setup() {
	m_udp.begin(m_udp_target_port);

}


bool JniUdpSender::send(int16_t x, int16_t y){
    int beginOK = m_udp.beginPacket(m_udp_target_ip, m_udp_target_port);
    if (beginOK == 0) { // Problem occured!
        // Serial.println("UDP connection failed");
        return false;
    }

    byte packetBuffer[PACKET_BUFFER_SIZE];
    packetBuffer[0] = x & 0xFF;
    packetBuffer[1] = (x >> 8) & 0xFF;
    packetBuffer[2] = y & 0xFF;
    packetBuffer[3] = (y >> 8) & 0xFF;
    auto packetSize = sizeof(packetBuffer);
    auto written = m_udp.write(packetBuffer, packetSize);

    auto okay = m_udp.endPacket();
    if (!okay || written != PACKET_BUFFER_SIZE) {
        // Serial.print("IP=");
        // Serial.print(m_udp_target_ip);
        // Serial.print(", ok=");
        // Serial.print(okay);
        // Serial.print(", size=");
        // Serial.print(PACKET_BUFFER_SIZE);
        // Serial.print(", written=");
        // Serial.println(written);
        // Serial.println("Reinitialize UDP");
        m_udp.begin(m_udp_target_port);
        return false;
    }
    return true;
}