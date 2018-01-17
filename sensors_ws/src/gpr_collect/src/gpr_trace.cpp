#include <iostream>
#include <stdint.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include "gpr_collect/gpr_trace.h"

using namespace std;

Gpr_trace::Gpr_trace(){

}

void Gpr_trace::_Init(uint8_t* raw_trace, size_t trace_size){
	traceSize_ = trace_size;
	_ReadRawTrace(raw_trace);
	_SetTraceMessage();
}

void Gpr_trace::_ReadRawTrace(uint8_t* raw_trace){
	memcpy(rawTrace_,raw_trace,traceSize_);
}

void Gpr_trace::_SetTraceMessage(void){
	_SetHeader();
	_ReadDataStamp();
	_SetStatusReport();
	_SetTraceData();

}

void Gpr_trace::_SetHeader(void){
	headerSize_ = (rawTrace_[1]<<8)|(rawTrace_[0]);
	char temp[7];
	_hex2char(rawTrace_[3],temp);
	strcpy(headerID_, temp);
	_hex2char(rawTrace_[2],temp);
	strcat(headerID_, temp);
//	headerID_ = (rawTrace_[3]<<8)|(rawTrace_[2]);
}

void Gpr_trace::_ReadDataStamp(void){
	uint8_t dataStamp_raw[28];
	for(int i = 0; i<28; i++){
		dataStamp_raw[i] = rawTrace_[4+i];
	}
	dataStamp_._Init(dataStamp_raw);
}

void Gpr_trace::_SetStatusReport(void){
	traceStatusFlag_ = (rawTrace_[35]<<24)|(rawTrace_[34]<<16)
			  |(rawTrace_[33]<<8)|(rawTrace_[32]);
	numStacks_ = (rawTrace_[37]<<8)|(rawTrace_[36]);
	hardwareFlag_ = (rawTrace_[39]<<8)|(rawTrace_[38]);
}

void Gpr_trace::_SetTraceData(void){
	for(int i = 0; i<(traceSize_-headerSize_)/2; i++){
		traceData_[i] = (rawTrace_[headerSize_+i*2+1]<<8)|(rawTrace_[headerSize_+i*2]);
	}
}

void Gpr_trace::_hex2char(uint8_t in, char* out){

	stringstream ssm_;
	ssm_<<hex<<(int)in;
	char temp[4];
	ssm_>>temp;
	if(strlen(temp)==1){
		temp[1] = temp[0];
		temp[0] = '0';
		temp[2] = 0;
	}
	memcpy(out, temp, 3);
}

void Gpr_trace::_report(void){
//	cout<<"Trace message report: "<<endl;
//	cout<<"Trace size: "<<traceSize_<<endl;
//	cout<<"Header size: \t\t"<<(int)headerSize_<<endl;
//	cout<<"Header ID: \t\t"<<headerID_<<endl;
//	cout<<"Stamp count: \t\t"<<(int)dataStamp_.count_<<endl;
	cout<<"Trace number: \t\t"<<(int)dataStamp_.traceNumber_<<endl;
//	cout<<"OdoTick: \t\t"<<(int)dataStamp_.odoTick_<<endl;
//	cout<<"TracePos: \t\t"<<(double)dataStamp_.tracePos_<<endl;
//	cout<<"Duration: \t\t"<<(double)dataStamp_.duration_<<endl;
//	cout<<"Trace Status Flag: \t"<<(int)traceStatusFlag_<<endl;
//	cout<<"Number of Stacks: \t"<<(int)numStacks_<<endl;
//	cout<<"Hardware flag: \t\t"<<(int)hardwareFlag_<<endl;
//	cout<<"Trace Data: ......"<<endl;
	for(int i = 0; i<(traceSize_-headerSize_)/2; i++){
		cout<<traceData_[i]<<" ";
	}
//	cout<<"\nTrace Data report done......"<<endl;
//	cout<<"Trace message report done."<<endl;
}

void Gpr_trace::_SaveToFile(char* file_path){
	ofstream output_file(file_path, ios::app);
	if(!output_file){
		cerr<<"Fail to create the data printout file: "
		    <<file_path<<endl;
	}
//	output_file<<"Trace message report: "<<endl;
//	output_file<<"Trace size: "<<traceSize_<<endl;
//	output_file<<"Header size: \t\t"<<(int)headerSize_<<endl;
//	output_file<<"Header ID: \t\t"<<headerID_<<endl;
//	output_file<<"Stamp count: \t\t"<<(int)dataStamp_.count_<<endl;
	output_file<<"\nTrace number: \t\t"<<(int)dataStamp_.traceNumber_<<endl;
//	output_file<<"OdoTick: \t\t"<<(int)dataStamp_.odoTick_<<endl;
//	output_file<<"TracePos: \t\t"<<(double)dataStamp_.tracePos_<<endl;
//	output_file<<"Duration: \t\t"<<(double)dataStamp_.duration_<<endl;
//	output_file<<"Trace Status Flag: \t"<<(int)traceStatusFlag_<<endl;
//	output_file<<"Number of Stacks: \t"<<(int)numStacks_<<endl;
//	output_file<<"Hardware flag: \t\t"<<(int)hardwareFlag_<<endl;
//	output_file<<"Trace Data: ......"<<endl;
	for(int i = 0; i<(traceSize_-headerSize_)/2; i++){
		output_file<<traceData_[i]<<" ";
	}
//	output_file<<"\nTrace Data report done......"<<endl;
//	output_file<<"Trace message report done."<<endl;
	output_file.close();
}
