#include <Arduino.h>
#include "jni_shared_types.h"
#include "jni_controller_display.h"
#include "jni_input_controller.h"
#include "jni_power_reader.h"
#include "jni_wifi.h"
#include "jni_config.h"

#define FREQ_100_HZ 10
#define FREQ_10_HZ 100
#define FREQ_5_SECS 5000


void readInputTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(FREQ_100_HZ);
	InputController inputController(UDP_RECEIVER_SOCKET_IP, UDP_RECEIVER_SOCKET_PORT);
	inputController.setup(ESP32_HOST_MAC);
	while (true) {
		inputController.loop100Hz();
		vTaskDelay(xFrequency);
	}
}


void displayTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(FREQ_10_HZ);
	ControllerDisplay controllerDisplay(UDP_RECEIVER_SOCKET_IP);
	controllerDisplay.setup();
	
	while(true) {
		controllerDisplay.loop10Hz();
		vTaskDelay(xFrequency);
	}
}


void readPowerTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(FREQ_5_SECS);
	PowerReader powerReader;
	while (true) {
		powerReader.updatePowerStatus();
		vTaskDelay(xFrequency);
	}
}


void setup() {
	Serial.begin(115200);

	connectionStatus.isWifiConnected = false;
	setWifiStatusIP_v4(NO_IP);
	connectionStatus.isBaseConnectionWorking = false;
	connectionStatus.isControllerConnected = false;

	char out_ip[MAX_IP_LENGTH];
	connect_wifi(out_ip, WIFI_SSID, WIFI_PASS);
	if (strcmp(out_ip, NO_IP) != 0) {
		Serial.printf("Connected with IP address: %s\n", out_ip);
		setWifiStatusIP_v4(out_ip);
		connectionStatus.isWifiConnected = true;

		xTaskCreate(displayTask, "displayTask", 4096, NULL, 1, NULL);
		xTaskCreate(readInputTask, "readInputTask", 4096, NULL, 1, NULL);	
		xTaskCreate(readPowerTask, "readPowerTask", 4096, NULL, 1, NULL);
	}

}

void loop() {
	// We don't need to do anything here.
}