#define WIFI_SETUP 1

#if WIFI_SETUP == 1
	#define WIFI_SSID      "Loxodonta"
	#define WIFI_PASS      "Twitch7%Carton%Driller%Bluish"
	#define UDP_RECEIVER_SOCKET_IP "192.168.199.233"  // Backup JNI Proto Car
#elif WIFI_SETUP == 2
	#define WIFI_SSID	  "Talpa"	
	#define WIFI_PASS	  "#K9bC5PRON3Lr3MQmJZtLgB#ax*Tr2kK96yb^83g&lfK%Te2F7Soai2TqPgJA&u"
	#define UDP_RECEIVER_SOCKET_IP "192.168.8.233"  // Talpa test rig
#endif

// #define UDP_RECEIVER_SOCKET_IP "192.168.199.201"  // Test Rig
// #define UDP_RECEIVER_SOCKET_IP "192.168.199.118"  // Test Rig
// #define UDP_RECEIVER_SOCKET_IP "192.168.199.245"  // NZXT Linux PC

#define UDP_RECEIVER_SOCKET_PORT 8080
#define ESP32_HOST_MAC "e8:9f:6d:25:49:26"
