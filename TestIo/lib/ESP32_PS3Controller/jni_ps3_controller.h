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
		bool _cross_pressed = false;
		bool _square_pressed = false;
		bool _triangle_pressed = false;
		bool _circle_pressed = false;

		static JniPs3Controller s_instance;
};
