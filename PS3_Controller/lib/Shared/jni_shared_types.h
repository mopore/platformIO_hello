#pragma once

#include <Arduino.h>
#include <string>

#define MAX_IP_LENGTH 16


typedef struct {
	int16_t x;
	int16_t y;
} CarInput;

extern volatile CarInput carInput;


typedef struct {
	float batteryVoltage;
} PowerStatus;

extern volatile PowerStatus powerStatus;


typedef struct {
	bool isWifiConnected;
	bool isControllerConnected;
	bool isBaseConnectionWorking;
	char ip_v4[MAX_IP_LENGTH];
} ConnectionSatus;

extern volatile ConnectionSatus connectionStatus;

void setWifiStatusIP_v4(const char* ipv4);
const char* getWifiStatusIP_v4();