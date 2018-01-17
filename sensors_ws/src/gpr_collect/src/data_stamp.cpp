#include <iostream>
#include <stdint.h>
#include <cstring>
#include <bitset>
#include "gpr_collect/data_stamp.h"

using namespace std;

Data_stamp::Data_stamp(void){

}

void Data_stamp::_Init(uint8_t* raw_stamp){
	_ReadRawStamp(raw_stamp);
	_SetDataStamp();
}

void Data_stamp::_ReadRawStamp(uint8_t* raw_stamp){
	memcpy(rawStamp_, raw_stamp, stampSize_);
}

void Data_stamp::_SetDataStamp(void){
	count_ = (rawStamp_[3]<<24)|(rawStamp_[2]<<16)
		 |(rawStamp_[1]<<8)|rawStamp_[0];
	traceNumber_ = (rawStamp_[7]<<24)|(rawStamp_[6]<<16)
		      |(rawStamp_[5]<<8)|rawStamp_[4];
	odoTick_ = (rawStamp_[11]<<24)|(rawStamp_[10]<<16)
		  |(rawStamp_[9]<<8)|rawStamp_[8];

	uint64_t traceT;
	traceT = ((uint64_t)rawStamp_[19]<<56)|((uint64_t)rawStamp_[18]<<48)
		   |((uint64_t)rawStamp_[17]<<40)|((uint64_t)rawStamp_[16]<<32)
		   |((uint64_t)rawStamp_[15]<<24)|((uint64_t)rawStamp_[14]<<16)
		   |((uint64_t)rawStamp_[13]<<8)|(uint64_t)rawStamp_[12];
	uint64_t durationT;
	durationT = ((uint64_t)rawStamp_[27]<<56)|((uint64_t)rawStamp_[26]<<48)
		   |((uint64_t)rawStamp_[25]<<40)|((uint64_t)rawStamp_[24]<<32)
		   |((uint64_t)rawStamp_[23]<<24)|((uint64_t)rawStamp_[22]<<16)
		   |((uint64_t)rawStamp_[21]<<8)|(uint64_t)rawStamp_[20];

	memcpy(&tracePos_,&traceT,64);
	memcpy(&duration_,&durationT,64);
}

void Data_stamp::_report(void){
	cout<<"Full report on the data stamp:"<<endl;
	cout<<"Count:\t"<<count_<<endl;
	cout<<"TraceNumber:\t"<<traceNumber_<<endl;
	cout<<"OdoTick:\t"<<odoTick_<<endl;
	cout<<"TracePos:\t"<<tracePos_<<endl;
	cout<<"Duration:\t"<<duration_<<endl;
	cout<<"Report Finished..."<<endl;
}

