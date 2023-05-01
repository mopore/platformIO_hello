#pragma once
#include <Arduino.h>
#include "jni_shared_types.h"
#include "jni_udp_receiver.h"


class InputController {
	public:
		explicit InputController(const uint16_t udp_target_port);
		void setup();
		void loop();
	private:
		JniUdpReceiver m_udpReceiver;
};