#pragma once

#include <Arduino.h>
#include <Ps3Controller.h>  // jvpernis/PS3 Controller Host@^1.1.0


class JniPs3Controller {
	public:
		static JniPs3Controller& getInstance();
		static void onNotify();
		void setup(const char* hostMacAddress);
		void loop();
	private:
	 	JniPs3Controller();
		void _handleNotify();
		int8_t _left_stick_x = 0;
		int8_t _right_stick_y= 0;

		static JniPs3Controller s_instance;
};
