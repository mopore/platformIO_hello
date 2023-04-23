#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_I2CDevice.h>

#include "jni_wifi.h"
#include "jni_udp_receiver.h"

static const char* ssid = "Loxodonta";
static const char* password = "witch7%Carton%Driller%Bluish";
static JniUdpReceiver receiver;


void setup() {
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);	
	String ip = connect_wifi();
	Serial.println(ip);
	digitalWrite(LED_BUILTIN, LOW);	
	receiver.setup();
}


void loop() {
	receiver.loop();
}