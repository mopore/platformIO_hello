#pragma once

#include <Arduino.h>
#include <UMS3.h>


class PowerChecker {
	public:
		PowerChecker();
		void setup();
		void loop();
	
	private:
		unsigned long m_lastBatteryCheck = 0;
		UMS3 m_ums3;
		void checkBattery();
};