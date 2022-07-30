/*******************************************************************
RFID Modbus code Version 1
Ver1: Initial commit by Low Chang Hong (29 Nov 2021)

Note for usage, unless explicitly mentioned, all length are in bytes, not word
******************************************************************/
#ifndef XS26_H
#define XS26_H

//including <Windows.h> leads to compile error. Please use Sleep() outside of class - 26nov2021
#include <chrono>
#include <thread>
#include <iostream>
#include <stdio.h>
#include <cstdint>
#include <string>

#define SLEEP_TIME 50ms
#define SLEEP(a) std::this_thread::sleep_for(a)

extern "C" {
#include <modbus.h>
}

using namespace std::chrono_literals;
using std::string;

class SafetyXS26
{
	modbus_t * modbusHandler;
	
public:
	uint16_t awRFID_input[300];
	int32_t diDeviceCount;
	int32_t diDeviceOnOff;


	int  connectModbus(modbus_t * mb, const char * ipAddress);
	int  connectModbus(const char * ipAddress);

	int readDeviceCount(int chainNumber);
	int readDeviceOnOff(int chainNumber);
	int readDoorSwitch(int switchNumber);

	void disconnectModbus();
	~SafetyXS26();

};

#endif
