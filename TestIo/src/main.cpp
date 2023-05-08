#include <Arduino.h>
#include <string>
#include <ArduinoJson.h>


// For creating some code you can use this assistant: 
// https://arduinojson.org/v6/assistant/
/*
	{
		"sensor": "gps",
		"time": 1351824120,
		"data": [
			48.75608,
			2.302038
		],
		"truth": true
	}
*/


const char* serializingExample() {
	StaticJsonDocument<128> doc;
	static char output[128];

	doc["sensor"] = "gps";
	doc["time"] = 1351824120;

	JsonArray data = doc.createNestedArray("data");
	data.add(48.75608);
	data.add(2.302038);
	doc["truth"] = true;

	serializeJson(doc, output);
	Serial.printf("Serialized JSON: %s\n", output);
	Serial.println();

	return output;
}


void deserializingExample(const char* input){
	StaticJsonDocument<192> doc;

	DeserializationError error = deserializeJson(doc, input);

	if (error) {
		Serial.print("deserializeJson() failed: ");
		Serial.println(error.c_str());
		return;
	}

	const char* sensor = doc["sensor"]; // "gps"
	Serial.printf("Sensor: %s\n", sensor);
	long time = doc["time"]; // 1351824120
	Serial.printf("Time: %ld\n", time);

	float data_0 = doc["data"][0]; // 48.75608
	float data_1 = doc["data"][1]; // 2.302038
	Serial.printf("Data: %f, %f\n", data_0, data_1);

	bool truth = doc["truth"]; // true
	Serial.printf("Truth: %s\n", truth ? "true" : "false");
	Serial.println();
}


void setup() {
	Serial.begin(115200);
	delay(10);
}


void loop() {
	Serial.println("Looping...");
	const char* serialized = serializingExample();
	deserializingExample(serialized);
	delay(10000);
}