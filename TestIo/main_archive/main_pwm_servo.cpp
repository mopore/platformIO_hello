#include <Arduino.h>
#include <ESP32Servo.h>
// Using: madhephaestus/ESP32Servo@^0.13.0
// https://github.com/madhephaestus/ESP32Servo/tree/master

Servo servo1;

// For SG90 servo (Continuous rotation)
const int maxBackward = 750;
const int maxForward = 2250;
const int stopPosition = (maxForward + maxBackward) / 2;
const int servoPin = 5;  // GPIO5
// servo1.writeMicroseconds(maxBackward);


// For a normal servo user the 'write' function
// const int lowest = 0;
// const int highest = 180;
// servo1.write(lowest);


ESP32PWM pwm;
void setup() {
	Serial.begin(115200);

	servo1.setPeriodHertz(50);      // Standard 50hz servo
	servo1.attach(servoPin, maxBackward, maxForward);
}

void loop() {
	Serial.println("Forward...");
	servo1.writeMicroseconds(maxBackward);
	delay(5000);
	Serial.println("Stop...");
	servo1.writeMicroseconds(stopPosition);
	delay(5000);
	Serial.println("Backward...");
	servo1.writeMicroseconds(maxForward);
	delay(5000);
	Serial.println("Stop...");
	servo1.writeMicroseconds(stopPosition);
	delay(5000);
}
