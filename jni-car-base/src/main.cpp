#include <Arduino.h>
#include "jni_shared_types.h"
#include "jni_controller_display.h"
#include "jni_input_reader.h"
#include "jni_power_reader.h"
#include "jni_wifi.h"
#include "jni_udp_receiver.h"
#include "jni_config.h"


void readInputTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(10); // .01 second	
	InputController inputReader(UDP_RECEIVER_SOCKET_PORT);

	inputReader.setup();
	while (true) {
		inputReader.loop();
		vTaskDelay(xFrequency);
	}
}


void displayTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(100); // .1 second
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

	char out_ip[MAX_IP_LENGTH];
	connect_wifi(out_ip, JNI_WIFI_SSID, JNI_WIFI_PASS);

	if (strcmp(out_ip, NO_IP) != 0) {
		Serial.printf("Connected with IP address: %s\n", out_ip);
		setWifiStatusIP_v4(out_ip);
		wifiStatus.isWifiConnected = true;
	
		xTaskCreate(displayTask, "displayTask", 4096, NULL, 1, NULL);
		xTaskCreate(readInputTask, "readInputTask", 4096, NULL, 1, NULL);	
		xTaskCreate(readPowerTask, "readPowerTask", 4096, NULL, 1, NULL);
	}
}


void loop() {
	// We don't need to do anything here.
}