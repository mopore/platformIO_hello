#pragma once

#include <Arduino.h>
#include "jni_shared_types.h"



class JniEngineControl {
	public:
		static JniEngineControl& getInstance();
		void setup();
		void loop10Hz();
	private:
		JniEngineControl();

		static JniEngineControl s_instance;
};