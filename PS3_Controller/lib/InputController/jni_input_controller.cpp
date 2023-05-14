#include "jni_input_controller.h"


InputController* InputController::s_instance = nullptr;


InputController::InputController(
	const char* udp_target_ip,
	const uint16_t udp_target_port
) :
	m_ps3Controller(JniPs3Controller::getInstance()),
	m_udpSender(udp_target_ip, udp_target_port)
{
    s_instance = this;
}


void InputController::setup(const char* esp32HostMac) {
	m_udpSender.setup();
	m_ps3Controller.setup(esp32HostMac);
}


void InputController::loop100Hz() {
	try {
		m_ps3Controller.loop();
		bool sentResult = false;
		if (connectionStatus.isControllerConnected) {
			sentResult = m_udpSender.send(carInput.x, carInput.y);
		}
		connectionStatus.isBaseConnectionWorking = sentResult;
	}
	catch (const std::exception& e) {
		Serial.print("Exception: ");
		Serial.println(e.what());
	}
}
