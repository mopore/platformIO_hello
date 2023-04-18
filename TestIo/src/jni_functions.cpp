#include "jni_functions.h"
#include <Arduino.h>

void jniFunction() {
	Person p("John", 30);
	String message = p.toString();
	Serial.println(message);
}


Person::Person(const String name, int age) {
	this->_name = name;
	this->_age = age;
}

String Person::toString() {
	return "Name: " + this->_name + ", Age: " + this->_age;
}
