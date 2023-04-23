#pragma once

#include "Arduino.h"

void jniFunction();

class Person {
	public:
		Person(const String name, int age);
		String toString();

	private:
		String _name;
		int _age;
};