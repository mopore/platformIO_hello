#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

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

#endif
