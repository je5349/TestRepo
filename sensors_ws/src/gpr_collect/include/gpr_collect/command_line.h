#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <stdint.h>
#include <stdlib.h>


class Command_line
{
public:
	Command_line(char*, char*, char*, char*, int, char*);
	void _setLength();
	void _setDestination(char*);
	void _setSourceAddr(char*);
	void _setCommandNum(char*);
	int _setMessageType(char*);
	int _setSessionId(int);
	size_t _setOptionalData(char*);
	void _generateCommand(void);
	size_t _char2hex(char*, uint8_t*);
	void _checkString(char*, char*);

	size_t size;
	uint8_t cmd_line[1024];

private:
	uint8_t length[4];
	uint8_t destination;
	uint8_t sourceAddr;
	uint8_t commandNum;
	uint8_t messageType;
	uint8_t sessionId[2];
	uint8_t data[1024];
	uint8_t cmd_num_res[12];
};


#endif
