#pragma once

#include <Arduino.h>
#include <string>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
// #include <Fonts/FreeMono9pt7b.h>
#include "jni_shared_types.h"


class ControllerDisplay {
	public:
		explicit ControllerDisplay(const std::string& target_ipv4);
		void setup();
		void loop10Hz();
	private:
		const std::string m_target_ipv4;
};