#include "safetyXS26.h"

int SafetyXS26::connectModbus(const char * ipAddress) {

	modbusHandler = modbus_new_tcp(ipAddress, 502);
	if (modbusHandler == NULL) {
		fprintf(stderr, "Unable to allocate libmodbus context\n");
		return -1;
	}
	if (modbus_connect(modbusHandler) == -1) {
		fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
		modbus_free(modbusHandler);
		return -1;
	}
	return 0;
}

int SafetyXS26::connectModbus(modbus_t * mb, const char * ipAddress) {

	mb = modbus_new_tcp(ipAddress, 502);
	if (mb == NULL) {
		fprintf(stderr, "Unable to allocate libmodbus context\n");
		return -1;
	}
	if (modbus_connect(mb) == -1) {
		fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
		modbus_free(mb);
		return -1;
	}
	return 0;	
}


int SafetyXS26::readDeviceCount(int chainNumber) {
	int MBaddr = 1767 + 16 * chainNumber;
	int tc = modbus_read_registers(modbusHandler, MBaddr, 2, (uint16_t*)&diDeviceCount);
	if (tc == -1) {
		fprintf(stderr, "device count read failed: %s\n", modbus_strerror(errno));
		return -1;
	}

	return diDeviceCount;
}

int SafetyXS26::readDeviceOnOff(int chainNumber) {
	int MBaddr = 1769 + 16 * chainNumber;
	int tc = modbus_read_registers(modbusHandler, MBaddr, 2, (uint16_t*)&diDeviceOnOff);
	if (tc == -1) {
		fprintf(stderr, "device count read failed: %s\n", modbus_strerror(errno));
		return -1;
	}
	return diDeviceOnOff;
}

int SafetyXS26::readDoorSwitch(int switchNumber) {
	//retrieve data from address of the VOstatus register
	int MBaddr,bit;
	uint16_t wVOStatus;
	switch (switchNumber) {
		case 1:
			MBaddr = 902;
			bit = 13;
			break;
		case 2:
			MBaddr = 902;
			bit = 14;
			break;
		case 3:
			MBaddr = 902;
			bit = 15;
			break;
		case 4:
			MBaddr = 903;
			bit = 0;
			break;
		default:
			printf("Invalid switch number requested\n");
			return -1;
	}
	int tc = modbus_read_registers(modbusHandler, MBaddr, 1, &wVOStatus);
	if (tc == -1) {
		fprintf(stderr, "door state read failed: %s\n", modbus_strerror(errno));
		return -1;
	}
	//extract data from bit (optional)
	int doorState;
	doorState = (wVOStatus>> bit)&1;
	return doorState;
}

void SafetyXS26::disconnectModbus() {
	modbus_close(modbusHandler);
	modbus_free(modbusHandler);
	printf("Closing modbus connection\n");
	return;
}

SafetyXS26::~SafetyXS26() {
	modbus_close(modbusHandler);
	modbus_free(modbusHandler);
	printf("Closing modbus connection\n");
	
}
