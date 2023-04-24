#pragma once
#include <Arduino.h>
#include "jni_shared_types.h"


class InputReader {
	public:
		InputReader();
		void setup();
		void loop();
	private:
		int16_t m_lastx;
		int16_t m_lasty;
};