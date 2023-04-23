#include <Arduino.h>
#include "jni_input_reader.h"
#include "jni_controller_display.h"
#include "jni_input_reader.h"

#define CORE_0 0
#define CORE_1 1


void readInputTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(10); // .01 second	
	InputReader inputReader;
	inputReader.setup();
	while (true) {
		inputReader.loop();
		vTaskDelay(xFrequency);
	}
}

void displayTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(100);

	ControllerDisplay controllerDisplay;
	controllerDisplay.setup();
	
	while(true) {
		controllerDisplay.loop();
		vTaskDelay(xFrequency);
	}
}

void setup() {
	Serial.begin(115200);
	// Set the core manually.
	xTaskCreatePinnedToCore(displayTask, "receiverTask", 4096, NULL, 1, NULL, CORE_0);
	xTaskCreatePinnedToCore(readInputTask, "printerTask", 4096, NULL, 1, NULL, CORE_1);	

}

void loop() {
	// We don't need to do anything here.
}