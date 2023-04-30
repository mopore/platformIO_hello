#pragma once

#include <Arduino.h>
#include <AsyncUDP.h>
#include "jni_shared_types.h"


#define UDP_RECEIVER_SOCKET_PORT 8080
#define UDP_RECEIVER_PACKAGE_SIZE 4	


class JniUdpReceiver {
	public:
	 	JniUdpReceiver();
		void setup();
	private:
		AsyncUDP udp;
};
