#pragma once

#include <Arduino.h>
#include <AsyncUDP.h>
#include <esp_wifi.h>


#define UDP_RECEIVER_SOCKET_PORT 8080
#define UDP_RECEIVER_PACKAGE_SIZE 4	


class JniUdpReceiver {
	public:
	 	JniUdpReceiver();
		void setup();
		void loop();
	private:
		AsyncUDP udp;
		int packetsCounter;
		int loopCounter;
		IPAddress myIp;
};
