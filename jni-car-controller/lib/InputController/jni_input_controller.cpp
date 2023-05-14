#include "jni_input_controller.h"

#define Y_MAX 127
#define Y_MIN -128
#define X_MAX 127
#define X_MIN -126

InputController* InputController::s_instance = nullptr;

// Initialize the static map for button names
std::map<uint8_t, String> InputController::buttonNames;


InputController::InputController(
	const char* udp_target_ip,
	const uint16_t udp_target_port
) :
	m_seesaw(),
	m_joy(m_seesaw),
	m_udpSender(udp_target_ip, udp_target_port)
{
	m_lastx = 0;
	m_lasty = 0;
    s_instance = this;

	buttonNames[BUTTON_DOWN] = "DOWN";
	buttonNames[BUTTON_UP] = "UP";
	buttonNames[BUTTON_LEFT] = "LEFT";
	buttonNames[BUTTON_RIGHT] = "RIGHT";
	buttonNames[BUTTON_SEL] = "SELECT";
}


void InputController::onJoystickEvent(int8_t xIn, int8_t yIn){
	if (s_instance != nullptr) {
		s_instance->handleJoystickEvent(xIn, yIn);
	}
}


void InputController::handleJoystickEvent(int8_t xIn, int8_t yIn){
	// We only want to read the x-axis for steering input.
	int xOut = 0;
	// int yOut = 0;
	if (xIn > 0) {
		xOut = ((float)xIn / X_MAX) * 100;
	} else {
		xOut = ((float)xIn / X_MIN) * -100;
	}
	// if (yIn > 0) {
	// 	yOut = ((float)yIn / Y_MAX) * 100;
	// } else {
	// 	yOut = ((float)yIn / Y_MIN) * -100;
	// }
	this->m_lastx = xOut;
	// this->m_lasty = yOut;
	// Serial.print(xOut); Serial.print(" : "); Serial.println(yOut);
}


void InputController::onButtonEvent(FJBUTTON* buttons, uint8_t count){
	if (s_instance != nullptr) {
		s_instance->handleButtonEvent(buttons, count);
	}
}


void InputController::handleButtonEvent(FJBUTTON* buttons, uint8_t count){
	for(int i = 0; i < count; i++) {
		if (buttons[i].hasChanged) {
			// We only use the buttons for throttle and reverse.
			// Serial.print("Button ");
			// String buttonName = buttonNames[buttons[i].pinId];
			// Serial.print(buttonName);
			// Serial.print(": ");
			// Serial.println(buttons[i].pressed);
			if (BUTTON_RIGHT == buttons[i].pinId){
				if (buttons[i].pressed) {
					// Serial.println("100% throttle");
					this->m_lasty = 100;
				}
				else {
					// Serial.println("0% throttle");
					this->m_lasty = 0;
				}
			}
			else if (BUTTON_DOWN == buttons[i].pinId){
				if (buttons[i].pressed) {
					// Serial.println("100% reverse");
					this->m_lasty = -100;
				}
				else {
					// Serial.println("0% reverse");
					this->m_lasty = 0;
				}
			}
		}
	}
}


void InputController::setup() {
	m_joy.begin();	
	m_joy.registerJoystickCallback(&InputController::onJoystickEvent);
	m_joy.registerButtonCallback(&InputController::onButtonEvent);
	m_udpSender.setup();
}


void InputController::loop100Hz() {
	carInput.x = m_lastx;
	carInput.y = m_lasty;
	m_joy.update();
	try {
		bool sentResult = m_udpSender.send(m_lastx, m_lasty);
		connectionStatus.isUdpWorking = sentResult;
	}
	catch (const std::exception& e) {
		Serial.print("Exception: ");
		Serial.println(e.what());
	}
}
