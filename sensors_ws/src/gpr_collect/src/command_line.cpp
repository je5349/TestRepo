#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <stdint.h>
#include <sstream>
#include "gpr_collect/command_line.h"

using namespace std;

Command_line::Command_line(char* des, char* src, char* cmd, char* msg, int id, char* data){

	_char2hex("634041424748494b50576162",cmd_num_res);
	_setDestination(des);
	_setSourceAddr(src);
	_setCommandNum(cmd);
	_setMessageType(msg);
	_setSessionId(id);
	size = _setOptionalData(data) + 10;
	_checkString(cmd, data);
	_setLength();
	_generateCommand();

}

void Command_line::_setLength(void){
	size_t len = size;
	length[3] = len/256;
	len = len - length[3]*256;
	length[2] = len/256;
	len = len - length[2]*256;
	length[1] = len/256;
	len = len - length[1]*256;
	length[0] = len;
}

void Command_line::_setDestination(char* des){
	_char2hex(des, &destination);
	if(destination<64||destination>127)
		cout<<"The destination address entered is wrong."<<endl;
}

void Command_line::_setSourceAddr(char* src){
	_char2hex(src, &sourceAddr);
	if(sourceAddr>63)//hex: 0x3f
		cout<<"The source address entered is wrong."<<endl;
}

void Command_line::_setCommandNum(char* cmd){
	_char2hex(cmd, &commandNum);
	int count = 0;
	for(int i = 0; i<12; i++){
		if(commandNum!=cmd_num_res[i])
			count++;
	}
	if(count == 12){
		cout<<"The command number entered is wrong."<<endl;
	}
}

int Command_line::_setMessageType(char* msg){

	string response = "response";
	string request = "request";
	if(response.compare(msg)==0){
		_char2hex("03", &messageType);
		return 0;
	}
	if(request.compare(msg)==0){
		_char2hex("02", &messageType);
		return 0;
	}

	cout<<"The message type entered is wrong."<<endl;
	return -1;
}

int Command_line::_setSessionId(int id){

	if(id>65535||id<0){
		cout<<"Session Id number is out of range..."<<endl;
		return -1;
	}

	size_t sid = id;
	sessionId[1] = sid/256;
	sid = sid - sessionId[1]*256;
	sessionId[0] = sid;
	return 0;
}

size_t Command_line::_setOptionalData(char* dt){

	size_t size;
	size = _char2hex(dt, data);
	return size;
}

void Command_line::_generateCommand(void){

	for (int i = 0; i<4; i++){
		cmd_line[i] = length[i];
	}

	cmd_line[4] = destination;
	cmd_line[5] = sourceAddr;
	cmd_line[6] = commandNum;
	cmd_line[7] = messageType;
	cmd_line[8] = sessionId[0];
	cmd_line[9] = sessionId[1];
	for (int i = 0; i<size-10; i++){
		cmd_line[10+i] = data[i];
	}
}

size_t Command_line::_char2hex(char* in, uint8_t* out){

	size_t out_size = strlen(in)/2;
	unsigned short oneHex;
	for(int i = 0; i<out_size; i++){
		stringstream buffer;
		buffer<<in[2*i]<<in[2*i+1];
		buffer>>hex>>oneHex;
		out[i] = oneHex;
	}
	return out_size;
}

void Command_line::_checkString(char* cmd, char* data){
	char cmd_c[10] = "49";
	int flag;
	if(strcmp(cmd,cmd_c) == 0){
		for(int i = 0; i<(size-10)*2; i+=2){
			if(data[i] == '0'&&data[i+1] == '0'){
				size = 11+i/2;
				break;
			}
		}
	}
	

}
