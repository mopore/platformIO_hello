#include "jni_input_reader.h"
#include <SPI.h>
#include <Adafruit_seesaw.h>

#define Y_MAX 127
#define Y_MIN -128
#define X_MAX 127
#define X_MIN -126


InputReader* InputReader::s_instance = nullptr;

// Initialize the static map for button names
std::map<uint8_t, String> InputReader::buttonNames;


InputReader::InputReader() :
	m_seesaw(),
	m_joy(m_seesaw)
{
	m_lastx = 0;
	m_lastx = 0;
    s_instance = this;

	buttonNames[BUTTON_DOWN] = "DOWN";
	buttonNames[BUTTON_UP] = "UP";
	buttonNames[BUTTON_LEFT] = "LEFT";
	buttonNames[BUTTON_RIGHT] = "RIGHT";
	buttonNames[BUTTON_SEL] = "SELECT";
}


void InputReader::onJoystickEvent(int8_t xIn, int8_t yIn){
	if (s_instance != nullptr) {
		s_instance->handleJoystickEvent(xIn, yIn);
	}
}


void InputReader::handleJoystickEvent(int8_t xIn, int8_t yIn){
	int xOut = 0;
	int yOut = 0;
	if (xIn > 0) {
		xOut = ((float)xIn / X_MAX) * 100;
	} else {
		xOut = ((float)xIn / X_MIN) * -100;
	}
	if (yIn > 0) {
		yOut = ((float)yIn / Y_MAX) * 100;
	} else {
		yOut = ((float)yIn / Y_MIN) * -100;
	}
	this->m_lastx = xOut;
	this->m_lasty = yOut;
	// Serial.print(xOut); Serial.print(" : "); Serial.println(yOut);
}


void InputReader::onButtonEvent(FJBUTTON* buttons, uint8_t count){
	if (s_instance != nullptr) {
		s_instance->handleButtonEvent(buttons, count);
	}
}


void InputReader::handleButtonEvent(FJBUTTON* buttons, uint8_t count){
	for(int i = 0; i < count; i++) {
		if (buttons[i].hasChanged) {
			Serial.print("Button ");
			String buttonName = buttonNames[buttons[i].pinId];
			Serial.print(buttonName);
			Serial.print(": ");
			Serial.println(buttons[i].pressed);
		}
	}
}


void InputReader::setup() {
	m_joy.begin();	
	m_joy.registerJoystickCallback(&InputReader::onJoystickEvent);
	m_joy.registerButtonCallback(&InputReader::onButtonEvent);
}


void InputReader::loop() {
	carInput.x = m_lastx;
	carInput.y = m_lasty;
	m_joy.update();
}
