#include "jni_controller_display.h"

#define TITEL_COL 0
#define TITEL_Y 0

#define LABELS_Y 20
#define VALUES_Y LABELS_Y + 10

#define COORDINATE_X_COL 0
#define COORDINATE_Y_COL 35
#define COORDINATE_WIDTH 30

#define BAT_COL 70
#define TEXT_WIDTH 30

#define IP_COL 0
#define LABEL_IP_Y 47
#define VALUE_IP_Y LABEL_IP_Y + 10

#define MODE_COL 98
#define LABEL_MODE_Y 47
#define VALUE_MODE_Y LABEL_MODE_Y + 10

#define NO_CONNECTION "<No Connection>"

#define LABEL_TITLE "JNI CAR PS3 CONTROL"
#define LABEL_IP "Base IP:"
#define LABEL_POWER "Power:"
#define LABEL_X "X:"
#define LABEL_Y "Y:"
#define LABEL_MODE "Mode:"

#define TEXT_LOW "LOW"
#define TEXT_MED "MED"
#define TEXT_HIGH "HIGH"

#define TEXT_OPERATIVE "OP"
#define TEXT_PS3_WAITING "PS3?"
#define TEXT_NETWORK_WAITING "NET?"

static Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
static GFXcanvas1 xCanvas = GFXcanvas1(COORDINATE_WIDTH, 10);
static GFXcanvas1 yCanvas = GFXcanvas1(COORDINATE_WIDTH, 10);
static GFXcanvas1 powerCanvas = GFXcanvas1(TEXT_WIDTH, 10);
static GFXcanvas1 modeCanvas = GFXcanvas1(TEXT_WIDTH, 10);

ControllerDisplay::ControllerDisplay(const std::string& target_ipv4)
    : m_target_ipv4(target_ipv4) {
}


void ControllerDisplay::setup() {
	delay(250); // wait for the OLED to power up
	display.begin(0x3C, true); // Address 0x3C default
	Serial.println("OLED is online.");

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

	// Draw title
	display.setCursor(TITEL_COL, TITEL_Y);
	display.print(LABEL_TITLE);
	display.drawLine(TITEL_COL, (TITEL_Y + 12), 128, (TITEL_Y + 12), SH110X_WHITE);

	// Draw coordinate labels
	display.setCursor(COORDINATE_X_COL, LABELS_Y);
	display.print(LABEL_X);
	display.setCursor(COORDINATE_Y_COL, LABELS_Y);
	display.print(LABEL_Y);

	// Draw battery label
	display.setCursor(BAT_COL,LABELS_Y);
	display.print(LABEL_POWER);

	// Draw IP label
	display.setCursor(IP_COL, LABEL_IP_Y);
	display.print(LABEL_IP);

	// Draw the target IP address
	display.setCursor(IP_COL, VALUE_IP_Y);
	display.print(m_target_ipv4.c_str());

	// Draw UDP label
	display.setCursor(MODE_COL, LABEL_MODE_Y);
	display.print(LABEL_MODE);

	display.display();
}


void ControllerDisplay::loop10Hz() {

	// Draw the X coordinate
	xCanvas.fillScreen(0);
	xCanvas.setCursor(0,0);
	xCanvas.printf("%d%%", carInput.x);
	display.drawBitmap(
		COORDINATE_X_COL, VALUES_Y, 
		xCanvas.getBuffer(), 
		COORDINATE_WIDTH, 10, 
		SH110X_WHITE, SH110X_BLACK
	);

	// Draw the Y coordinate
	yCanvas.fillScreen(0);
	yCanvas.setCursor(0,0);
	yCanvas.printf("%d%%", carInput.y);
	display.drawBitmap(
		COORDINATE_Y_COL, VALUES_Y, 
		yCanvas.getBuffer(), 
		COORDINATE_WIDTH, 10, 
		SH110X_WHITE, SH110X_BLACK
	);

	// Draw the battery status
	powerCanvas.fillScreen(0);
	powerCanvas.setCursor(0,0);
	if (powerStatus.batteryVoltage < 3.3) {
		powerCanvas.printf(TEXT_LOW);
	}
	else if (powerStatus.batteryVoltage < 3.5) {
		powerCanvas.printf(TEXT_MED);
	}
	else {
		powerCanvas.printf(TEXT_HIGH);
	}
	display.drawBitmap(
		BAT_COL, VALUES_Y, 
		powerCanvas.getBuffer(), 
		TEXT_WIDTH, 10, 
		SH110X_WHITE, SH110X_BLACK
	);

	// Draw the mode status
	modeCanvas.fillScreen(0);
	modeCanvas.setCursor(0,0);
	if (connectionStatus.isControllerConnected){
		if (connectionStatus.isBaseConnectionWorking) {
			modeCanvas.printf(TEXT_OPERATIVE);
		}
		else {
			modeCanvas.printf(TEXT_NETWORK_WAITING);
		}
	}
	else {
		modeCanvas.printf(TEXT_PS3_WAITING);
	}
	display.drawBitmap(
		MODE_COL, VALUE_MODE_Y, 
		modeCanvas.getBuffer(), 
		TEXT_WIDTH, 10, 
		SH110X_WHITE, SH110X_BLACK
	);

	display.display();
}
