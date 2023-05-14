#include "jni_shared_types.h"
#include "jni_ps3_controller.h"

static int16_t toPerCent(int8_t value) {
	return (int) (value * 100 / 127);
}

JniPs3Controller JniPs3Controller::s_instance;


JniPs3Controller& JniPs3Controller::getInstance() {
	return JniPs3Controller::s_instance;
}


JniPs3Controller::JniPs3Controller() {
}


void JniPs3Controller::onNotify() {
	JniPs3Controller::s_instance._handleNotify();
}


void JniPs3Controller::setup(const char* hostMacAddress) {
	Ps3.begin(hostMacAddress);
	Serial.printf("Bluetooth MAC address of ESP32 controller base: %s\n", hostMacAddress);
	
	Ps3.attachOnConnect([](){
		Serial.println("PS3 controller connected");
		connectionStatus.isControllerConnected = true;
	});	
	Ps3.attachOnDisconnect([](){
		Serial.println("PS3 controller disconnected");
		connectionStatus.isControllerConnected = false;
	});

	Ps3.attach([](){
		JniPs3Controller::onNotify();
	});
	Serial.println("Waiting for PS3 controller...");
}


void JniPs3Controller::loop() {
	
}

void JniPs3Controller::_handleNotify() {
	if( abs(Ps3.event.analog_changed.stick.lx) > 1 ){
		auto x_raw = Ps3.data.analog.stick.lx;
		auto x = toPerCent(x_raw);
		carInput.x = x;
		// Serial.print(" x="); Serial.print(x);
		// Serial.println();
	}
	if( abs(Ps3.event.analog_changed.stick.ry) > 1 ){
		auto y_raw = Ps3.data.analog.stick.ry;
		auto y = toPerCent(y_raw) * -1;
		carInput.y = y;
		// Serial.print(" y="); Serial.print(y);
		// Serial.println();
	}
}