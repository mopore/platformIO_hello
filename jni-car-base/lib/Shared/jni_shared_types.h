#pragma once

#include <Arduino.h>

#define NO_IP "0.0.0.0"


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
	char ip_v4[16];
} WifiStatus;

void setIP_v4Status(String newIp);
String getIP_v4Status(void);

extern volatile WifiStatus wifiStatus;