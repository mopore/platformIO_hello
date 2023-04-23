#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "jni_udp_sender.h"


JniUdpSender::JniUdpSender() {
	m_previousMillis = 0;
	m_x = -100;
	m_y = 100;
}


void JniUdpSender::setup() {
	udp.begin(UDP_RECEIVER_SOCKET_PORT);

}


void JniUdpSender::loop() {
    const unsigned long SEND_INTERVAL_MS = 10; // 0.01 seconds
    unsigned long currentMillis = millis();
    if (currentMillis - m_previousMillis >= SEND_INTERVAL_MS) {
        byte packetBuffer[4];
        packetBuffer[0] = m_x & 0xFF;
        packetBuffer[1] = (m_x >> 8) & 0xFF;
        packetBuffer[2] = m_y & 0xFF;
        packetBuffer[3] = (m_y >> 8) & 0xFF;

		udp.beginPacket(UDP_RECEIVER_SOCKET_IP, UDP_RECEIVER_SOCKET_PORT);
		udp.write(packetBuffer, 4);
		udp.endPacket();

        updateXY();
        m_previousMillis = currentMillis;
		Serial.printf("x: %d, y: %d\n", m_x, m_y);
    }
}


void JniUdpSender::updateXY() {
    m_x++;
    if (m_x > 100) {
        m_x = -100;
        m_y--;
        if (m_y < -100) {
            m_y = 100;
        }
    }
}
