#include <Arduino.h>

#define JNI_TEST_EXCEPTION "JNI_TEST_EXCEPTION"

double createException(){
	throw std::runtime_error(JNI_TEST_EXCEPTION);
	return 1;
}

void setup() {
	Serial.begin(115200);
	delay(10);
}


void loop() {
	delay(1000);
	try {
		createException();
		Serial.println("No exception");
	}
	catch(const std::exception& e) {
		Serial.println("Caught exception");
		if (strcmp(e.what(), JNI_TEST_EXCEPTION) == 0) {
			Serial.println("Exception is JNI_TEST_EXCEPTION");
		}
		else {
			Serial.println("Exception is not JNI_TEST_EXCEPTION");
		}
	}
	

}