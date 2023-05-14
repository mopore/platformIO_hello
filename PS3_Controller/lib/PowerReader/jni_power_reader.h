#pragma once

#include <Arduino.h>
#include "jni_shared_types.h"


class PowerReader {
	public:
		PowerReader();
		void updatePowerStatus();
	
	private:
		float getBatteryVoltage(); 
};