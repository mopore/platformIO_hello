#include "jni_input_reader.h"

InputController::InputController(const uint16_t udp_target_port) 
: m_udpReceiver(udp_target_port) {
}


void InputController::setup() {
	m_udpReceiver.setup();
}


void InputController::loop() {
	// Nothing to do here
}
