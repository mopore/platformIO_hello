#pragma once

#include <Arduino.h>
#include <WiFiUdp.h>


class JniUdpSender {
	public:
	 	JniUdpSender();
		void setup();
		void loop();
	private:
		void updateXY();
		void send(int16_t x, int16_t y);
		ulong m_previousMillis;
		int16_t m_x;
		int16_t m_y;
		WiFiUDP m_udp;
};
