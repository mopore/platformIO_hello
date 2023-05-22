#include <Arduino.h>
#include <pwmWrite.h>  // Include dlloydev/ESP32 ESP32S2 AnalogWrite@^4.3.4

#define LEFT_FRONT_PIN 14
#define LEFT_MIN_PULSE 750
#define LEFT_MAX_PULSE 2250

#define RIGHT_FRONT_PIN 12
#define RIGHT_MIN_PULSE 740
#define RIGHT_MAX_PULSE 2240

#define STEERING_PIN 6
#define STEERING_MAX_LEFT 49
#define STEERING_MAX_RIGHT 139
#define STEERING_REVERESE true
#define STEERING_MIN_PULSE 600
#define STEERING_MAX_PULSE 2400

const int leftStop = (LEFT_MAX_PULSE + LEFT_MIN_PULSE) / 2;
const int rightStop = (RIGHT_MAX_PULSE + RIGHT_MIN_PULSE) / 2;
const int steeringCenter = (STEERING_MAX_LEFT + STEERING_MAX_RIGHT) / 2;


Pwm pwm = Pwm();

void setup() {
	Serial.begin(115200);
	
}


void testSteering(){
	for (int pos = STEERING_MAX_LEFT; pos <= STEERING_MAX_RIGHT; pos++) {
		Serial.println(pos);
		pwm.writeServo(STEERING_PIN, pos);
		delay(150);
	}
	for (int pos = STEERING_MAX_RIGHT; pos >= STEERING_MAX_LEFT; pos--) {
		Serial.println(pos);
		pwm.writeServo(STEERING_PIN, pos);
		delay(150);
	}
}


void loop() {
	Serial.println("Starting");
	for (int pos = 0; pos <= 180; pos++) {
		Serial.println(pos);
		// pwm.writeServo(LEFT_FRONT_PIN, 180);  // forward
		pwm.writeServo(LEFT_FRONT_PIN, 96);  // stop
		// pwm.writeServo(LEFT_FRONT_PIN, 180);  // backward

		// pwm.writeServo(RIGHT_FRONT_PIN, 0);  // forward
		pwm.writeServo(RIGHT_FRONT_PIN, 90);  // stop
		// pwm.writeServo(RIGHT_FRONT_PIN, 180);  // backward
		
		pwm.writeServo(STEERING_PIN, steeringCenter);
		delay(100);
	}
	for (int pos = 180; pos >= 0; pos--) {
		Serial.println(pos);
		pwm.writeServo(LEFT_FRONT_PIN, 96);
		pwm.writeServo(RIGHT_FRONT_PIN, 90);
		pwm.writeServo(STEERING_PIN, steeringCenter);
		delay(100);
	}
}