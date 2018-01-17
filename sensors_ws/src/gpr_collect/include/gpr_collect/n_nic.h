#ifndef N_NIC_H
#define N_NIC_H

#include <netinet/in.h>
#include <stdint.h>
#include <stdlib.h>
#include <queue>
#include "gpr_collect/command_line.h"
#include "gpr_collect/s_server.h"
#include "gpr_collect/gpr_trace.h"


class n_nic
{
public:
	n_nic();
// functions
	bool _initNIC(char*, int, std::string);

	bool _CmdChanPort(void);	//40	
	void _DeviceInfo(char*);	//63	//NNIC@@
	void _AttachDataChanPort(char*);//41	//listen speak auto
	void _DetachDataChanPort(void);//42
	void _InitPorts(char*);		//47
	void _CreateGPRPort(char*);	//48
	void _InitPortProtocol(int);	//49
	size_t _SendFromBuffer(signed long);	//4B
	void _DataAcquisition(char*);	//50	//start stop auto check
	void _DataStamp(void);		//
	void _GetPortDeviceUID(char*);	//61	//port_addr
	int _GetPortProtocolParamDef(char*, int);	//62

	void _readAllDeviceInfo(void);
	void _readAllDeviceUID(void);
	void _readAllDefaultParam(char*);	// "save","discard"
	void _setAllParam(char*);		//"single","multiple","default"
	void _readParamFromFile(char*);		// "single", "multiple"

	void _loopTerminal(void);
	void _loopTerminal_a1(void);
	void _loopTerminal_a2(void);

	void _FreeRunTracesCollection(void);

	void _nic_close(void);

	std::string getSampleInterval(void);
	std::string getFrequency(void);


// variables
	bool Exit = false;
	std::vector<Gpr_trace> trace_stack_;

private:
// functions
	void _get_sessionId(void);
	void _num2string(int, int, char*);
	int _string2num(char*);
	void _hex2string(char*, size_t, char*);
	size_t _read(int, uint8_t*, size_t);
	void _write(int, Command_line);

	void _printBufferIntoFiles(void);

	void _printData(uint8_t*);
	void _uint8ToHex(uint8_t, char*);

// variables
	char nn_addr_[5]; // address assigned to NIC
	char aa_addr_[5]; // starting address for NIC ports
	char gpr_port_[5];// address for GPR port

	int n_ports;
	int n_params;
	int sessionId;
	int cmd_chan_;
	int data_chan_;
	int req_chan_;

	int buffer_output_;
	int data_id = 1;

	char nic_port_addr[13][5];
	char nic_port_uid[13][8];
	
	char** gpr_param_list;
	char** gpr_param_char;

	size_t buf_size = 1024;
	uint8_t buffer[1024];

	std::string file_folder_;
	std::vector<uint8_t> trace_vector_;

	int buffer_empty_counter_ = 0;

	s_server req_server_, cmd_server_, data_server_;
	bool dataChanPort_open_ = false;
	bool cmdChanPort_open_ = false;
	char dataChanMode_[8];

	bool dataAcquisition_start_ = false;

	std::string sampleInterval_;
	std::string frequency_;

};


#endif
