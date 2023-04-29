#include <Arduino.h>
#include "jni_shared_types.h"
#include "jni_controller_display.h"
#include "jni_input_reader.h"
#include "jni_wifi.h"

static const char* ssid = "Loxodonta";
static const char* password = "witch7%Carton%Driller%Bluish";

volatile CarInput carInput;


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
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);	
	String ip = connect_wifi();
	Serial.print("JNI Car Controller IP address: ");
	Serial.println(ip);
	digitalWrite(LED_BUILTIN, LOW);	

	xTaskCreate(displayTask, "displayTask", 4096, NULL, 1, NULL);
	xTaskCreate(readInputTask, "readInputTask", 4096, NULL, 1, NULL);	
}

void loop() {
	// We don't need to do anything here.
}