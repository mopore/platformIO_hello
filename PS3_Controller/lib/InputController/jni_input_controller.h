#pragma once
#include <Arduino.h>
// #include <string>
// #include <map>
// #include <SPI.h>
#include "jni_shared_types.h"
#include "jni_udp_sender.h"
#include "jni_ps3_controller.h"


class InputController {
	public:
		explicit InputController(
			const char* udp_target_ip,
			const uint16_t udp_target_port
		);
		void setup(const char* esp32HostMac);
		void loop100Hz();

	private:
		JniPs3Controller m_ps3Controller;
		JniUdpSender m_udpSender;
		static InputController* s_instance;  // Used to pass callback events.
};