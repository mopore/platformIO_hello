#include "jni_power_reader.h"

#define VBATPIN A13

PowerReader::PowerReader() {
}


void PowerReader::updatePowerStatus() {
	powerStatus.batteryVoltage = getBatteryVoltage();
}


float PowerReader::getBatteryVoltage() {
	float measuredvbat = analogReadMilliVolts(VBATPIN);
	measuredvbat *= 2;    // we divided by 2, so multiply back
	measuredvbat /= 1000; // convert to volts!
	return measuredvbat;
}