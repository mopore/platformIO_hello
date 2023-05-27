#include <Arduino.h>
#include <memory>

/*
	This demonstrates that after the move, p1 no longer owns the memory and p2 is now the owner of 
	the memory. std::unique_ptr does not allow copying, but it does allow moving. 

	Using std::unique_ptr for Simple Cases: When dynamic allocation is necessary and ownership 
	semantics are simple, std::unique_ptr can be a good tool, as it provides some safety benefits 
	without the overhead of std::shared_ptr.
*/

void setup() {
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	std::unique_ptr<String> p1(new String("Hello"));
	std::unique_ptr<String> p2 = std::move(p1); // Ownership transferred to p2
	
	// After move, p1 no longer owns the memory
	if(p1) {
		Serial.print("p1: "); 
		Serial.println(p1->c_str()); 
		// Alternative way to print the string:
		Serial.println("p1: " + *p1);
	} else {
		Serial.println("p1 is no longer owning the memory.");
	}

	if(p2) {
		Serial.print("p2: ");
		Serial.println(p2->c_str());
	} else {
		Serial.println("p2 is not owning any memory.");
	}
}

void loop() {
	// put your main code here, to run repeatedly:
}