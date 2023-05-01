#pragma once
#include <map>
#include <Arduino.h>
#include "jni_shared_types.h"
#include "FeatherJoyWing.h"
#include "jni_udp_sender.h"


class InputController {
	public:
		explicit InputController(const JniUdpSender& udpSender);
		void setup();
		void loop();

		// Used to pass callback events.
		static void onJoystickEvent(int8_t xIn, int8_t yIn);
		static void onButtonEvent(FJBUTTON* buttons, uint8_t count);

	private:
		int16_t m_lastx;
		int16_t m_lasty;
		Adafruit_seesaw m_seesaw;
		FeatherJoyWing m_joy;
		JniUdpSender m_udpSender;
		
		static std::map<uint8_t, String> buttonNames;
		static InputController* s_instance;  // Used to pass callback events.

		void handleJoystickEvent(int8_t xIn, int8_t yIn);
		void handleButtonEvent(FJBUTTON* buttons, uint8_t count);
};