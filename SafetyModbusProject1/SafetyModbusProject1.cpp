#include<stdio.h>
#include <iostream>
#include "safetyXS26.h"
#include <Windows.h>

extern "C" {
	#include <modbus.h>
}

int main()
{
	SafetyXS26 mock2;
	string ip;
	int ch = 0;

	std::cout << "This is sample test program for SafetyXS26\n";
	std::cout << "Connecting via modbus to SafetyXS26\n";
	std::cout << "Please key in IP to connect: \t";
	std::cin >> ip;
	std::cout << ip << std::endl;

	try {
		if (mock2.connectModbus(ip.c_str())) 
			throw "Invalid IP address.\n";
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
		return -1;
	}
	std::cout << "Controller Connected. ";
	do
	{
		std::cout << "Please select channel: \n";
		if (!(std::cin >> ch)) {	//error occurred
			std::cout << "invalid input" << std::endl;
			std::cin.clear();		//Clear the error
			std::cin.ignore();		//discard input
		}
	} while (ch <1  || ch > 8);
	std::cout << "DeviceCount in ISD:" << ch << " is " << mock2.readDeviceCount(ch) << "\n";
	std::cout << "DeviceOnOff in ISD:" << ch << " is " << mock2.readDeviceOnOff(ch) << "\n";
	std::cin.clear();
	std::cin.ignore();
	getchar();
	//std::this_thread::sleep_for(20s);
}
