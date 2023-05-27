#include <Arduino.h>
#include <memory>

/*
	In this example, p1 and p2 both point to the same String and share ownership of it.
	They can both be used to access and modify the String, and when both p1 and p2 are destroyed 
	(for example, if they go out of scope), the String will be deleted. 

	This is a simple way to share a resource between different parts of a program, with automatic 
	memory management.

	Avoiding std::shared_ptr Unless Necessary: In most microcontroller applications, 
	std::shared_ptr is overkill. The overhead of reference counting and the increased complexity 
	are usually not worth it. You'd typically only use it in complex scenarios where ownership is 
	shared and the lifetime of objects is difficult to predict.
*/

void setup() {
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	std::shared_ptr<String> p1(new String("Hello"));

	std::shared_ptr<String> p2 = p1; // p1 and p2 now share ownership

	// Access value
	if(p1) {
		Serial.print("p1: ");
		Serial.println(p1->c_str()); // Prints: p1: Hello
	} else {
		Serial.println("p1 is not owning any memory.");
	}

	if(p2) {
		// Alternative way to print the string:
		Serial.println("p2: " + *p2); // Prints: p2: Hello
	} else {
		Serial.println("p2 is not owning any memory.");
	}
}


void loop() {
	// put your main code here, to run repeatedly:
}