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
	int ch = 0;

	std::cout << "This is sample test program for SafetyXS26\n";
	std::cout << "Connecting via modbus to SafetyXS26\n";
	if (mock2.connectModbus("192.168.0.38") != 0) {
		std::cout << "Connection failed. Please check hardware and resolve error. Exiting program\n";
	}
	else {
		std::cout << "Connected.\n";
		do
		{
			std::cout << "What's the chain number to check?\n";
			if (!(std::cin >> ch)) {//error occurred
				std::cout << "invalid input" << std::endl;
				std::cin.clear();//Clear the error
				std::cin.ignore(); //discard input
			}
		} while (ch != 1 && ch != 2);
		//mock2.readDeviceCount(ch);
		std::cout << "DeviceCount in ISD:" << ch << " is " << mock2.readDeviceCount(ch) << "\n";
		std::cout << "DeviceOnOff in ISD:" << ch << " is " << mock2.readDeviceOnOff(ch) << "\n";
	}
}
