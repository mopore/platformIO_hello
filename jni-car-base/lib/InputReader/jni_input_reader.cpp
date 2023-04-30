#include "jni_input_reader.h"

InputReader::InputReader() {
}


void InputReader::setup() {
	m_udpReceiver.setup();
}


void InputReader::loop() {
	// Nothing to do here
}
