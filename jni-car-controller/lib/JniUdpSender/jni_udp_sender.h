#pragma once

#include <Arduino.h>
#include <string>
#include <WiFiUdp.h>

class JniUdpSender {
	public:
	 	explicit JniUdpSender(
			const std::string& udp_target_ip,
			const uint16_t udp_target_port
		);
		void setup();
		void send(int16_t x, int16_t y);
	private:
		WiFiUDP m_udp;
		const std::string m_udp_target_ip;
		const uint16_t m_udp_target_port;
};
