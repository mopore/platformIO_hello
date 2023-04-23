
#include "jni_controller_display.h"


#define COORDINATE_X_COL 0
#define COORDINATE_Y_COL 35
#define COORDINATE_WIDTH 30

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
GFXcanvas1 xCanvas = GFXcanvas1(COORDINATE_WIDTH, 10);
GFXcanvas1 yCanvas = GFXcanvas1(COORDINATE_WIDTH, 10);


int x = -100;
int y = 100;
ControllerDisplay::ControllerDisplay() {
	

}


void ControllerDisplay::setup() {

}


void ControllerDisplay::loop() {

}
