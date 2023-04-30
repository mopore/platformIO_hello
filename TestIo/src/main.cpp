#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_I2CDevice.h>


const int vbatPin = 2; // The pin you want to read from (IO2)
// const int vbus_sense = 32; // The pin you want to read from (IO32)


void setup() {
  Serial.begin(115200);

  // Configure the ADC resolution and attenuation
  analogReadResolution(12); // Set the ADC resolution to 12 bits
  analogSetAttenuation(ADC_11db); // Set the ADC input attenuation (ADC_0db, ADC_2_5db, ADC_6db, ADC_11db)
  pinMode(vbatPin, INPUT); // Set the pin mode to INPUT for analog reading

//   pinMode(vbus_sense, INPUT); // Set the pin mode to INPUT for analog reading
}

void loop() {
	float analogValue = analogRead(vbatPin); // Read the analog value from IO2
	float voltage = analogValue / 5371;
	Serial.print("Battery voltage: ");
	Serial.println(voltage);             // Print the value to the serial monitor
	
	// int digitalValue = digitalRead(vbus_sense); // Read the analog value from IO2
	// Serial.print("USB connected: ");
	// Serial.println(digitalValue);             // Print the value to the serial monitor

	delay(1000);                             // Wait for a second before reading again
}