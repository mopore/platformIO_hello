#pragma once

#include <Arduino.h>
#include <WiFiUdp.h>


class JniUdpSender {
	public:
	 	JniUdpSender();
		void setup();
		void send(int16_t x, int16_t y);
	private:
		WiFiUDP m_udp;
};
