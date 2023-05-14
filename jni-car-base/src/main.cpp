#include <Arduino.h>
#include "jni_shared_types.h"
#include "jni_controller_display.h"
#include "jni_input_reader.h"
#include "jni_power_reader.h"
#include "jni_wifi.h"
#include "jni_udp_receiver.h"
#include "jni_config.h"

#define FREQ_100HZ 10  // Every 10ms of 1000ms
#define FREQ_10HZ 100  // Every 100ms of 1000ms
#define FREQ_5Sec 5000


void readInputTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(FREQ_100HZ);
	InputReader inputReader(UDP_RECEIVER_SOCKET_PORT);

	inputReader.setup();
	while (true) {
		inputReader.loop100Hz();
		vTaskDelay(xFrequency);
	}
}


void displayTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(FREQ_10HZ);
	ControllerDisplay controllerDisplay;

	controllerDisplay.setup();
	while(true) {
		controllerDisplay.loop10Hz();
		vTaskDelay(xFrequency);
	}
}


void readPowerTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(FREQ_5Sec);
	PowerReader powerReader;
	powerReader.setup();
	while (true) {
		powerReader.updatePowerStatus();
		vTaskDelay(xFrequency);
	}
}


void setup() {
	Serial.begin(115200);
	connectionStatus.isWifiConnected = false;
	connectionStatus.isUdpWorking = false;
	setWifiStatusIP_v4(NO_IP);

	char out_ip[MAX_IP_LENGTH];
	connect_wifi(out_ip, TALPA_SSID, TALPA_PASS);

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