#ifndef DATA_STAMP_H
#define DATA_STAMP_H

#include <iostream>
#include <stdint.h>


class Data_stamp{
public:
	Data_stamp(void);
// functions
	void _Init(uint8_t*);
	void _report(void);
// variables
	unsigned int count_;
	unsigned int traceNumber_;
	unsigned int odoTick_;
	double tracePos_;
	double duration_;

private:
// functions
	void _ReadRawStamp(uint8_t*);
	void _SetDataStamp(void);
// variables
	uint8_t rawStamp_[36];	// 28 should be enough
	size_t stampSize_ = 28;
};

#endif
