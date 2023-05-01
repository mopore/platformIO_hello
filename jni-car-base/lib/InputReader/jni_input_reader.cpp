#include "jni_input_reader.h"

InputController::InputController() {
}


void InputController::setup() {
	m_udpReceiver.setup();
}


void InputController::loop() {
	// Nothing to do here
}
