#include "jni_udp_sender.h"

#define UDP_RECEIVER_SOCKET_IP "192.168.199.245"
// #define UDP_RECEIVER_SOCKET_IP "192.168.199.240"
#define UDP_RECEIVER_SOCKET_PORT 8080
#define UDP_RECEIVER_PACKAGE_SIZE 4	


#define PACKET_BUFFER_SIZE 4

JniUdpSender::JniUdpSender() {
	m_previousMillis = 0;
	m_x = -100;
	m_y = 100;
}


void JniUdpSender::setup() {

}


void JniUdpSender::loop() {
    const unsigned long SEND_INTERVAL_MS = 10; // 0.01 seconds
    unsigned long currentMillis = millis();
    if (currentMillis - m_previousMillis >= SEND_INTERVAL_MS) {
        send(m_x, m_y);
        updateXY();
        m_previousMillis = currentMillis;
		Serial.printf("x: %d, y: %d\n", m_x, m_y);
    }
}


void JniUdpSender::send(int16_t x, int16_t y){

        int connOK = m_udp.begin(UDP_RECEIVER_SOCKET_PORT);
        if (connOK == 0) {
            Serial.println("UDP could not get socket");
            return;
        }
		int beginOK = m_udp.beginPacket(UDP_RECEIVER_SOCKET_IP, UDP_RECEIVER_SOCKET_PORT);
        if (beginOK == 0) { // Problem occured!
            Serial.println("UDP connection failed");
            return;
        }

        byte packetBuffer[PACKET_BUFFER_SIZE];
        packetBuffer[0] = x & 0xFF;
        packetBuffer[1] = (x >> 8) & 0xFF;
        packetBuffer[2] = y & 0xFF;
        packetBuffer[3] = (y >> 8) & 0xFF;
        auto packetSize = sizeof(packetBuffer);
        if (packetSize != PACKET_BUFFER_SIZE) {
            Serial.println("Prepared packet size is not packet buffer size!");
            return;
        }   
		auto sentBytes = m_udp.write(packetBuffer, packetSize);
        if (sentBytes != PACKET_BUFFER_SIZE) {
            Serial.println("Sent packet size is not packet buffer size!");
            return;
        }

		m_udp.endPacket();
        m_udp.stop();
        Serial.println("UDP packet sent OKAY");
}


void JniUdpSender::updateXY() {
    m_x++;
    if (m_x > 100) {
        m_x = -100;
    }
        
    m_y--;
    if (m_y < -100) {
        m_y = 100;
    }
}
