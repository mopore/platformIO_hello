#include "jni_shared_types.h"
#include <cstring>


volatile CarInput carInput;


volatile PowerStatus powerStatus;


volatile WifiStatus wifiStatus;


void setWifiStatusIP_v4(const std::string &ipv4) {
	// Cast away volatile qualifier to allow assignment
	WifiStatus *non_volatile_wifiStatus = const_cast<WifiStatus *>(&wifiStatus);
	non_volatile_wifiStatus->ip_v4 = ipv4;
}


const std::string getWifiStatusIP_v4() {
	// Cast away volatile qualifier to allow access
	const WifiStatus *non_volatile_wifiStatus = const_cast<const WifiStatus *>(&wifiStatus);
	return non_volatile_wifiStatus->ip_v4;
}