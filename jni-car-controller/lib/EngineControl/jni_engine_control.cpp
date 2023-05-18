#include "jni_engine_control.h"

JniEngineControl JniEngineControl::s_instance;


JniEngineControl& JniEngineControl::getInstance(){
	return JniEngineControl::s_instance;
}


JniEngineControl::JniEngineControl() {
}


void JniEngineControl::setup() {
}


void JniEngineControl::loop10Hz() {
}
