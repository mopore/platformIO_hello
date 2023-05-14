#include <Arduino.h>

#define VBATPIN A13

float readBatteryVoltage() {
	float measuredvbat = analogReadMilliVolts(VBATPIN);
	measuredvbat *= 2;    // we divided by 2, so multiply back
	measuredvbat /= 1000; // convert to volts!
	return measuredvbat;
}


void setup() {
	Serial.println("Starting...");
	Serial.begin(115200);
}


void loop() {
	auto voltage = readBatteryVoltage();
	Serial.print("Battery voltage: " ); Serial.println(voltage);
	delay(1000);
}