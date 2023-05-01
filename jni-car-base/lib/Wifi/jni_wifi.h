#pragma once
#include <Arduino.h>
#include <string>

#define NO_IP "0.0.0.0"


std::string connect_wifi(const std::string& ssid, const std::string& password);