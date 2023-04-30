#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

void setup() {
	Serial.begin(115200);

	Serial.println("128x64 OLED FeatherWing test");
	delay(250); // wait for the OLED to power up
	display.begin(0x3C, true); // Address 0x3C default

	Serial.println("OLED begun");

	// Show image buffer on the display hardware.
	// Since the buffer is intialized with an Adafruit splashscreen
	// internally, this will display the splashscreen.
	display.display();
	delay(1000);

	// Clear the buffer.
	display.clearDisplay();
	display.display();

	display.setRotation(1);

	// text display tests
	display.setTextSize(1);
	display.setTextColor(SH110X_WHITE);
}


void loop() {
	display.clearDisplay();
	display.setCursor(0,0);
	ulong start = millis();
	display.println(start);
	display.display();
	delay(100);
}