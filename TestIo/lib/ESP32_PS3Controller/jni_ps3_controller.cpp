#include "jni_ps3_controller.h"


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
	String address = Ps3.getAddress();
	Serial.printf("Bluetooth MAC address of ESP32: %s\n", address.c_str());
	
	Ps3.attachOnConnect([](){
		Serial.println("Connected");
	});	
	Ps3.attachOnDisconnect([](){
		Serial.println("Disconnected");
	});

	Ps3.attach([](){
		JniPs3Controller::onNotify();
	});
	Serial.println("Waiting for connection...");
}


void JniPs3Controller::loop() {
	
}

void JniPs3Controller::_handleNotify() {
	if( Ps3.data.button.cross ){
		if (_cross_pressed == false) {
			Serial.println("Pressing the cross button");
			_cross_pressed = true;
		}
	}
	else {
		if (_cross_pressed == true) {
			Serial.println("Releasing the cross button");
			_cross_pressed = false;
		}
	}

	if( Ps3.data.button.square ){
		if (_square_pressed == false) {
			Serial.println("Pressing the square button");
			_square_pressed = true;
		}
	}
	else {
		if (_square_pressed == true) {
			Serial.println("Releasing the square button");
			_square_pressed = false;
		}
	}

	if( Ps3.data.button.triangle ){
		if (_triangle_pressed == false) {
			Serial.println("Pressing the triangle button");
			_triangle_pressed = true;
		}
	}
	else {
		if (_triangle_pressed == true) {
			Serial.println("Releasing the triangle button");
			_triangle_pressed = false;
		}
	}

	if( Ps3.data.button.circle ){
		if (_circle_pressed == false) {
			Serial.println("Pressing the circle button");
			_circle_pressed = true;
		}
	}
	else {
		if (_circle_pressed == true) {
			Serial.println("Releasing the circle button");
			_circle_pressed = false;
		}
	}

    //---------------- Analog stick value events ---------------
   if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
       Serial.print("Moved the left stick:");
       Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
       Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
       Serial.println();
    }

   if( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ){
       Serial.print("Moved the right stick:");
       Serial.print(" x="); Serial.print(Ps3.data.analog.stick.rx, DEC);
       Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ry, DEC);
       Serial.println();
   }

}