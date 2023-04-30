#include <Arduino.h>
#include "jni_shared_types.h"
#include "jni_controller_display.h"
#include "jni_input_reader.h"
#include "jni_power_reader.h"
#include "jni_wifi.h"

#define FREQ_100_HZ 10
#define FREQ_10_HZ 100
#define FREQ_5_SECS 5000


void readInputTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(FREQ_100_HZ);
	InputReader inputReader;
	inputReader.setup();
	while (true) {
		inputReader.loop();
		vTaskDelay(xFrequency);
	}
}


void displayTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(FREQ_10_HZ);

	ControllerDisplay controllerDisplay;
	controllerDisplay.setup();
	
	while(true) {
		controllerDisplay.loop();
		vTaskDelay(xFrequency);
	}
}


void readPowerTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(FREQ_5_SECS);
	PowerReader powerReader;
	powerReader.setup();
	while (true) {
		powerReader.updatePowerStatus();
		vTaskDelay(xFrequency);
	}
}


void setup() {
	Serial.begin(115200);
	wifiStatus.isWifiConnected = false;
	setIP_v4Status(NO_IP);

	String ip = connect_wifi();
	if (ip != NO_IP) {
		setIP_v4Status(ip);
		wifiStatus.isWifiConnected = true;
	}

	xTaskCreate(displayTask, "displayTask", 4096, NULL, 1, NULL);
	xTaskCreate(readInputTask, "readInputTask", 4096, NULL, 1, NULL);	
	xTaskCreate(readPowerTask, "readPowerTask", 4096, NULL, 1, NULL);
}

void loop() {
	// We don't need to do anything here.
}