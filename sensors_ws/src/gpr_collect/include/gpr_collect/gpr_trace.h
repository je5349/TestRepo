#ifndef GPR_TRACE_H
#define GPR_TRACE_H

#include <iostream>
#include <stdint.h>
#include "gpr_collect/data_stamp.h"

class Gpr_trace{

public:
	Gpr_trace();
// functions
	void _Init(uint8_t*, size_t);
	void _report(void);
	void _SaveToFile(char*);
// variables
	unsigned short headerSize_;
	char headerID_[10];
//	unsigned short headerID_;
	Data_stamp dataStamp_;
	unsigned int traceStatusFlag_;
	unsigned short numStacks_;
	unsigned short hardwareFlag_;

	signed short traceData_[1024];
	size_t traceSize_;

private:
// functions
	void _ReadRawTrace(uint8_t*);
	void _SetTraceMessage(void);
	void _SetHeader(void);
	void _ReadDataStamp(void);
	void _SetStatusReport(void);
	void _SetTraceData(void);

	void _hex2char(uint8_t, char*);

// variables
	uint8_t rawTrace_[1024];
};

#endif
