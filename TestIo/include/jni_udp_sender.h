#pragma once

#include <Arduino.h>
#include <WiFiUdp.h>

#define UDP_RECEIVER_SOCKET_IP "192.168.199.245"
#define UDP_RECEIVER_SOCKET_PORT 8080
#define UDP_RECEIVER_PACKAGE_SIZE 4	


class JniUdpSender {
	public:
	 	JniUdpSender();
		void setup();
		void loop();
	private:
		void updateXY();
		ulong m_previousMillis;
		int16_t m_x;
		int16_t m_y;
		WiFiUDP udp;
};
