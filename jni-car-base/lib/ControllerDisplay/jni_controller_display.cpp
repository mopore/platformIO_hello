#include "jni_controller_display.h"


#define COORDINATE_X_COL 0
#define COORDINATE_Y_COL 35
#define COORDINATE_WIDTH 30

#define BAT_COL 70
#define BAT_WIDTH 30

static Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
static GFXcanvas1 xCanvas = GFXcanvas1(COORDINATE_WIDTH, 10);
static GFXcanvas1 yCanvas = GFXcanvas1(COORDINATE_WIDTH, 10);
static GFXcanvas1 batCanvas = GFXcanvas1(BAT_WIDTH, 10);

ControllerDisplay::ControllerDisplay() {
}


void ControllerDisplay::setup() {
	Serial.println("128x64 OLED FeatherWing test");
	delay(250); // wait for the OLED to power up
	display.begin(0x3C, true); // Address 0x3C default

	Serial.println("OLED begun");

	// Show image buffer on the display hardware.
	// Since the buffer is intialized with an Adafruit splashscreen
	// internally, this will display the splashscreen.
	display.display();
	delay(1000);

	// General setup
	display.clearDisplay();
	display.display();
	display.setRotation(1);
	display.setTextSize(1);
	display.setTextColor(SH110X_WHITE);

	// Draw coordinate labels
	display.setCursor(COORDINATE_X_COL,0);
	display.print("X:");
	display.setCursor(COORDINATE_Y_COL,0);
	display.print("Y:");

	// Draw battery label
	display.setCursor(BAT_COL,0);
	display.print("BAT:");

	display.display();
}


void ControllerDisplay::loop() {

	xCanvas.fillScreen(0);
	xCanvas.setCursor(0,0);
	xCanvas.printf("%d%%", carInput.x);
	display.drawBitmap(
		COORDINATE_X_COL, 10, 
		xCanvas.getBuffer(), 
		COORDINATE_WIDTH, 10, 
		SH110X_WHITE, SH110X_BLACK
	);

	yCanvas.fillScreen(0);
	yCanvas.setCursor(0,0);
	yCanvas.printf("%d%%", carInput.y);
	display.drawBitmap(
		COORDINATE_Y_COL, 10, 
		yCanvas.getBuffer(), 
		COORDINATE_WIDTH, 10, 
		SH110X_WHITE, SH110X_BLACK
	);

	batCanvas.fillScreen(0);
	batCanvas.setCursor(0,0);
	if (powerStatus.usbPowerPresent) {
		batCanvas.printf("USB");
	}
	else if (powerStatus.batteryVoltage < 3.3) {
		batCanvas.printf("LOW");
	}
	else if (powerStatus.batteryVoltage < 3.5) {
		batCanvas.printf("MED");
	}
	else {
		batCanvas.printf("HIGH");
	}
	// batCanvas.printf("%.1fV", powerStatus.batteryVoltage);
	display.drawBitmap(
		BAT_COL, 10, 
		batCanvas.getBuffer(), 
		BAT_WIDTH, 10, 
		SH110X_WHITE, SH110X_BLACK
	);

	display.display();
}
