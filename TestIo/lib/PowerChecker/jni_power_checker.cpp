#include "jni_power_checker.h"

#define BATTERY_CHECK_INTERVAL 1000


PowerChecker::PowerChecker() {
	m_lastBatteryCheck = 0;
}


void PowerChecker::setup() {
  // Initialize all board peripherals, call this first
  m_ums3.begin();
}


void PowerChecker::loop() {
	if (m_lastBatteryCheck == 0 || millis() - m_lastBatteryCheck > BATTERY_CHECK_INTERVAL) {
		checkBattery();
		m_lastBatteryCheck = millis();
	}
}


void PowerChecker::checkBattery() {
	// Get the battery voltage, corrected for the on-board voltage divider
	// Full should be around 4.2v and empty should be around 3v
	float battery = m_ums3.getBatteryVoltage();
	Serial.println(String("Battery: ") + battery);

	if (m_ums3.getVbusPresent()) {
		Serial.println("USB power is present");
	} 
	else {
		Serial.println("USB power is not present");
		// Else, USB power is not present (running from battery)
		if (battery < 3.1) {
			// Uncomment the following line to sleep when the battery is critically low
			//esp_deep_sleep_start();
		} else if (battery < 3.3) {
			// Below 3.3v - red
		} 	
	}
}