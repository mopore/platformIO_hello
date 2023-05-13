#include <Arduino.h>
#include <Ps3Controller.h>

#define ESP32_HOST_MAC "e8:9f:6d:25:49:26"


static bool cross_pressed = false;
static bool square_pressed = false;
static bool triangle_pressed = false;
static bool circle_pressed = false;


void notify(){
	if( Ps3.data.button.cross ){
		if (cross_pressed == false) {
			Serial.println("Pressing the cross button");
			cross_pressed = true;
		}
	}
	else {
		if (cross_pressed == true) {
			Serial.println("Releasing the cross button");
			cross_pressed = false;
		}
	}

	if( Ps3.data.button.square ){
		if (square_pressed == false) {
			Serial.println("Pressing the square button");
			square_pressed = true;
		}
	}
	else {
		if (square_pressed == true) {
			Serial.println("Releasing the square button");
			square_pressed = false;
		}
	}

	if( Ps3.data.button.triangle ){
		if (triangle_pressed == false) {
			Serial.println("Pressing the triangle button");
			triangle_pressed = true;
		}
	}
	else {
		if (triangle_pressed == true) {
			Serial.println("Releasing the triangle button");
			triangle_pressed = false;
		}
	}

	if( Ps3.data.button.circle ){
		if (circle_pressed == false) {
			Serial.println("Pressing the circle button");
			circle_pressed = true;
		}
	}
	else {
		if (circle_pressed == true) {
			Serial.println("Releasing the circle button");
			circle_pressed = false;
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


void setup() {
	Serial.println("Starting...");

	Serial.begin(115200);
	Ps3.begin(ESP32_HOST_MAC);
	String address = Ps3.getAddress();
	Serial.printf("Bluetooth MAC address of ESP32: %s\n", address.c_str());

	Ps3.attach(notify);
	Ps3.attachOnConnect([](){
		Serial.println("Connected");
	});	
	Ps3.attachOnDisconnect([](){
		Serial.println("Disconnected");
	});
	Serial.println("Waiting for connection...");
}


void loop() {
}