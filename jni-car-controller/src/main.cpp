#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Fonts/FreeMono9pt7b.h>

#define COORDINATE_X_COL 0
#define COORDINATE_Y_COL 35
#define COORDINATE_WIDTH 30

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
GFXcanvas1 xCanvas = GFXcanvas1(COORDINATE_WIDTH, 10);
GFXcanvas1 yCanvas = GFXcanvas1(COORDINATE_WIDTH, 10);

int x = -100;
int y = 100;

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

	display.setCursor(COORDINATE_X_COL,0);
	display.print("X:");

	display.setCursor(COORDINATE_Y_COL,0);
	display.print("Y:");
	display.display();

}


void loop() {
	x++;
	if (x > 100) {
		x = -100;
	}
	y--;
	if (y < -100) {
		y = 100;
	}

	xCanvas.fillScreen(0);
	xCanvas.setCursor(0,0);
	xCanvas.printf("%d%%", x);
	display.drawBitmap(
		COORDINATE_X_COL, 10, 
		xCanvas.getBuffer(), 
		COORDINATE_WIDTH, 10, 
		SH110X_WHITE, SH110X_BLACK
	);

	yCanvas.fillScreen(0);
	yCanvas.setCursor(0,0);
	yCanvas.printf("%d%%", x);
	display.drawBitmap(
		COORDINATE_Y_COL, 10, 
		yCanvas.getBuffer(), 
		COORDINATE_WIDTH, 10, 
		SH110X_WHITE, SH110X_BLACK
	);

	display.display();
	delay(100);
}