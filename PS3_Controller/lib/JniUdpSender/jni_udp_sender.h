#pragma once

#include <Arduino.h>
#include <string>
#include <WiFiUdp.h>

class JniUdpSender {
	public:
	 	explicit JniUdpSender(
			const char* udp_target_ip,
			const uint16_t udp_target_port
		);
		void setup();
		bool send(int16_t x, int16_t y);
	private:
		WiFiUDP m_udp;
		const char* m_udp_target_ip;
		const uint16_t m_udp_target_port;
};
