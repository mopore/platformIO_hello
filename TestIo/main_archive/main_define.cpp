#include <Arduino.h>

#define SETUP 1

#if SETUP == 1
#define SSID "Loxodonta"
#else
#define SSID "COMP-NET"
#endif

void setup(void) {
	Serial.begin(115200);
	while (!Serial)
		delay(10);
}


void loop() {
	Serial.print("My SSID is: ");
	Serial.println(SSID);
	delay(3000);
}