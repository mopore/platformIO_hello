#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Fonts/FreeMono9pt7b.h>
#include "jni_input_reader.h"

extern volatile CarInput carInput;

class ControllerDisplay {
	public:
		ControllerDisplay();
		void setup();
		void loop();
};