#pragma once

#include <Arduino.h>
#include <string>



typedef struct {
	int16_t x;
	int16_t y;
} CarInput;

extern volatile CarInput carInput;


typedef struct {
	bool usbPowerPresent;
	float batteryVoltage;
} PowerStatus;

extern volatile PowerStatus powerStatus;


typedef struct {
	bool isWifiConnected;
	std::string ip_v4;
} WifiStatus;

extern volatile WifiStatus wifiStatus;

void setWifiStatusIP_v4(const std::string &ipv4);
const std::string getWifiStatusIP_v4();