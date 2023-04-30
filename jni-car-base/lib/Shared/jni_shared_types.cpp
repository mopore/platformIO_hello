#include "jni_shared_types.h"
#include <cstring>


volatile CarInput carInput;


volatile PowerStatus powerStatus;


volatile WifiStatus wifiStatus;


void setIP_v4Status(String newIp) {
	strncpy(
		const_cast<char*>(wifiStatus.ip_v4), 
		newIp.c_str(), 
		sizeof(wifiStatus.ip_v4)
	);
	wifiStatus.ip_v4[sizeof(wifiStatus.ip_v4) - 1] = '\0'; // Ensure the string is null-terminated
}


String getIP_v4Status() {
	return const_cast<char*>(wifiStatus.ip_v4);
}

