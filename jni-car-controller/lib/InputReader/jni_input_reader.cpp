#include "jni_input_reader.h"

InputReader::InputReader() {
	m_lastx = 0;
	m_lastx = 0;
}


void InputReader::setup() {
}


void InputReader::loop() {
	m_lastx++;
	if (m_lastx > 100) {
		m_lastx = -100;
		m_lasty++;
	}
	m_lasty--;
	if (m_lasty < -100) {
		m_lasty = 100;
	}
	carInput.x = m_lastx;
	carInput.y = m_lasty;
}
