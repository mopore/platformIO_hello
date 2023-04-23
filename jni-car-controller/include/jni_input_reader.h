#pragma once
#include <Arduino.h>

typedef struct {
  int16_t x;
  int16_t y;
} CarInput;


volatile CarInput carInput;

class InputReader {
	public:
		InputReader();
		void setup();
		void loop();
	private:
		int16_t m_lastx;
		int16_t m_lasty;
};