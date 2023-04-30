#include <Arduino.h>

typedef struct {
  int x;
  int y;
} Coordinates;


volatile Coordinates coordinates;


void receiverTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(10); // .01 second	
	int lastx = 0;
	int lasty = 0;
	while (true) {
		lastx++;
		if (lastx > 100) {
			lastx = -100;
			lasty++;
		}
		lasty--;
		if (lasty < -100) {
			lasty = 100;
		}
		coordinates.x = lastx;
		coordinates.y = lasty;

		vTaskDelay(xFrequency);
	}
}


void printerTask(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(1000); // 1 second	

	while (true) {
		Serial.print("x: ");
		Serial.print(coordinates.x);
		Serial.print(" y: ");
		Serial.println(coordinates.y);

		vTaskDelay(xFrequency);
	}
}


void setup() {
	Serial.begin(115200);
	
	// Set the core manually.
	xTaskCreatePinnedToCore(receiverTask, "receiverTask", 4096, NULL, 1, NULL, 0);
	xTaskCreatePinnedToCore(printerTask, "printerTask", 4096, NULL, 1, NULL, 1);

	// // This will automatically deploy the task on both cores.
	// xTaskCreate(receiverTask, "receiverTask", 4096, NULL, 1, NULL);
	// xTaskCreate(printerTask, "printerTask", 4096, NULL, 1, NULL);
}


void loop() {
	// We will leave this empty.
}