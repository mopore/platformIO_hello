#pragma once
#include <Arduino.h>
#include <string>

// #define JNI_ESP_WIFI_SSID      "Loxodonta"
// #define JNI_ESP_WIFI_PASS      "Twitch7%Carton%Driller%Bluish"


std::string connect_wifi(const std::string& ssid, const std::string& password);