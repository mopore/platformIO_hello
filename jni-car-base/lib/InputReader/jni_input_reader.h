#pragma once
#include <Arduino.h>
#include "jni_shared_types.h"
#include "jni_udp_receiver.h"


class InputReader {
	public:
		InputReader();
		void setup();
		void loop();
	private:
		JniUdpReceiver m_udpReceiver;
};