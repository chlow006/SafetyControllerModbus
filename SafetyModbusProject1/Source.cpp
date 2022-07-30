#include <iostream>
#include <modbus.h>

uint16_t readMb(modbus_t * mb) {
	uint16_t tagPresentwhere;
	int tc = modbus_read_registers(mb, 0xa, 1, &tagPresentwhere);
	if (tc == -1) {
		fprintf(stderr, "device count read failed: %s\n", modbus_strerror(errno));
		return -1;
	}
	return tagPresentwhere;
}

int main()
{
	std::cout << "Hello World!\n";
	modbus_t * mb;
	uint16_t tagPresentwhere;
	char ch = 0;

	mb = modbus_new_tcp("192.168.1.35", 502);
	if (mb == NULL) {
		fprintf(stderr, "Unable to allocate libmodbus context\n");
		return -1;
	}
	if (modbus_connect(mb) == -1) {
		fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
		modbus_free(mb);
		return -1;
	}
	std::cout << "Connected.\n";
	do
	{
		std::cout << "check?(y/n)\n";
		if (!(std::cin >> ch)) {//error occurred
			std::cout << "invalid input" << std::endl;
			std::cin.clear();//Clear the error
			std::cin.ignore(); //discard input
		}
		tagPresentwhere = readMb(mb);
		std::cout << "tagPresentwhere " << tagPresentwhere << "\n";
	} while (ch != 'n');


	return 0;
}
