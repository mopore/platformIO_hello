#include "jni_functions.h"
#include <Arduino.h>

void jniFunction() {
  Serial.println("Hello from JNI!");
}


Person::Person(const String name, int age) {
  this->_name = name;
  this->_age = age;
}

String Person::toString() {
  return "Name: " + this->_name + ", Age: " + this->_age;
}
