#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Neopixel LED for Unexpected Maker FeatherS3
#define PIN        40
#define NUMPIXELS 1 // Popular NeoPixel ring size
#define DELAYVAL 10 // Time (in milliseconds) to pause between pixels


static Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
static const uint32_t YELLOW = pixels.Color(255, 255, 0);


static uint32_t Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	WheelPos -= 170;
	return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


static void rainbow(){
	uint16_t i, j;

	for(j=0; j<256; j++) {
		for(i=0; i<pixels.numPixels(); i++) {
			pixels.setPixelColor(i, Wheel((i+j) & 255));
		}
		pixels.show();
		delay(DELAYVAL);
	}
}


void setup() {
	pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
	pixels.clear(); // Set all pixel colors to 'off'
	pixels.setBrightness(50); // Set brightness to about 1/5 (max = 255)
}


void loop() {
	rainbow();
	pixels.clear();
	pixels.show();
	delay(1000);

	pixels.setPixelColor(0, YELLOW);
	pixels.show();
	delay(1000);

	pixels.clear();
	pixels.show();
	delay(1000);
}