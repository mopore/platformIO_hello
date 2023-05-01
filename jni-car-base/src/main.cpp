#include <Arduino.h>
#include "jni_shared_types.h"
#include "jni_controller_display.h"
#include "jni_input_reader.h"
#include "jni_power_reader.h"
#include "jni_wifi.h"
#include "jni_udp_receiver.h"


void readInputTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(10); // .01 second	
	InputController inputReader;

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


void readPowerTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(5000); // 5 seconds
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
	setWifiStatusIP_v4(NO_IP);

	auto ip = connect_wifi();
	if (ip != NO_IP) {
		setWifiStatusIP_v4(ip);
		wifiStatus.isWifiConnected = true;

	}
	
	xTaskCreate(displayTask, "displayTask", 4096, NULL, 1, NULL);
	xTaskCreate(readInputTask, "readInputTask", 4096, NULL, 1, NULL);	
	xTaskCreate(readPowerTask, "readPowerTask", 4096, NULL, 1, NULL);
}


void loop() {
	// We don't need to do anything here.
}