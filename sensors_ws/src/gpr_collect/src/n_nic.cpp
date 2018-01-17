#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <stdint.h>
#include <bitset>
#include <sstream>
#include <cmath>
#include <ctime>
#include "gpr_collect/s_server.h"
#include "gpr_collect/n_nic.h"
#include "gpr_collect/gpr_trace.h"

using namespace std;


n_nic::n_nic(void){


	gpr_param_list = new char* [20];
	gpr_param_char = new char* [20];
	for(int i = 0; i<20; i++){
		gpr_param_list[i] = new char[256];
		gpr_param_char[i] = new char[256];
	}

}

bool n_nic::_initNIC(char* nic_addr_, int nic_chan_, string file_folder){

	// set up the parameter residing folder location
	file_folder_ = file_folder;

	// set up the nic address and nic connection-request channel
	strcpy(nn_addr_, nic_addr_);
	int aa_num_ = _string2num(nn_addr_)+10;
	_num2string(aa_num_,2,aa_addr_);
	_num2string(aa_num_+10,2,gpr_port_);
	req_chan_ = nic_chan_;
	srand(time(NULL));
	cmd_chan_ = rand()%1000+req_chan_+1;
	data_chan_ = rand()%1000+cmd_chan_+1;
	sessionId = 0;

	// set up the connection channel
	req_server_._initial(req_chan_);

	if(req_server_.Exit<0){
		cout<<"Couldn't connect to the NIC connection request channel "
		    <<req_chan_<<" ..."
		    <<endl;
		Exit = true;
	}

	// set up the command channel
	if(_CmdChanPort()==true){
		_InitPorts(aa_addr_);
		_CreateGPRPort(gpr_port_);
//		_InitPorts(aa_addr_);
		_setAllParam("single");	// "file" or "device"
//		_readAllDefaultParam("save");// "save" or "discard"
		_AttachDataChanPort("listen");
		_DataAcquisition("start");	// Free run mode
//		_DataAcquisition("auto");	// Trigger mode
//		_SendFromBuffer(1024);	
//		_loopTerminal();	
//		_FreeRunTracesCollection();
      return true;
	}
  else{
    return false;
  }
}

void n_nic::_FreeRunTracesCollection(void){

	signed long trace_size = 440;

	size_t return_size = _SendFromBuffer(trace_size);
	if(return_size > 0){
		_read(data_server_.messenger_, buffer, buf_size);

////////////////////////////////////Trace_queue//////////////////////////////
		for(int i = 0; i<return_size; i++){
//			trace_queue_.push(buffer[i]);
			trace_vector_.push_back(buffer[i]);
		}
////////////////////////////////////Trace_queue//////////////////////////////
	}

	while(trace_vector_.size()>=trace_size){
		uint8_t temp_trace[trace_size];
		for(int i = 0; i<trace_size && !trace_vector_.empty(); i++){
			temp_trace[i] = trace_vector_.front();
			trace_vector_.erase(trace_vector_.begin());
		}
		//Trace processing//
		Gpr_trace trace_msg_;
		trace_msg_._Init(temp_trace,trace_size);
//		trace_msg_._report();
		trace_stack_.push_back(trace_msg_);

	}
}

std::string n_nic::getSampleInterval(void){
	return sampleInterval_;
}

std::string n_nic::getFrequency(void){
	return frequency_;
}

void n_nic::_printBufferIntoFiles(void){
	char file_path[1024];
	strcpy(file_path, "/home/kexiao/Desktop/data");
	stringstream convert_;
	convert_<<data_id;
	data_id++;
	char path_num[24];
	convert_>>path_num;
	strcat(file_path, path_num);
	strcat(file_path, ".txt");
	ofstream printout(file_path, ios::out);
	if(!printout){
		cerr<<"Fail to create the data printout file: "
		    <<file_path<<endl;
	}
	else{
		for(int i = 0; i<buffer_output_; i++){
			char Hex_out[5];
			_uint8ToHex(buffer[i],Hex_out);
//			cout<<_uint8ToHex(buffer[buffer_output_])<<" ";
			printout<<Hex_out;
//			printout<<_uint8ToHex(buffer[buffer_output_]);
		}
	}
	printout.close();

}

void n_nic::_uint8ToHex(uint8_t data, char* convert_){
	stringstream ssm_;
	ssm_<<hex<<(int)data;
	ssm_>>convert_;
	if( strlen(convert_) == 1){
		convert_[1] = convert_[0];
		convert_[0] = '0';
		convert_[2] = 0;
	}
//	return convert_;

}

void n_nic::_DataStamp(void){

	char* command_num = "57";
	char* Err_type = "00";
//	char d_channel[10];
//	char data[16];
//	_num2string(cmd_chan_, 4,d_channel); 
//	strcpy(data,Err_type);
//	strcat(data,nn_addr_);
//	strcat(data,d_channel);

	//read from the request connection socket
	size_t real_size;
	real_size = _read(data_server_.messenger_, buffer, buf_size);

	
	cout<<"\nC57 Reading - Command line from the data channel..."<<endl;
	for(int i =0; i<10; i++){
		cout<<hex<<(int)buffer[i]<<" ";
	}
	cout<<endl;
	cout<<"The real size is: "<<real_size<<endl;
	cout<<"\nC57 Reading - Data from the data channel..."<<endl;
	for(int i =10; i<buf_size; i++){
		cout<<hex<<(int)buffer[i];
	}
	cout<<"\n"<<endl;

	char file_path[1024];
	strcpy(file_path, "/home/kexiao/Desktop/data");
	stringstream convert_;
	convert_<<data_id;
	data_id++;
	char path_num[24];
	convert_>>path_num;
	strcat(file_path, path_num);
	strcat(file_path, ".txt");
	ofstream printout(file_path, ios::out);
	if(!printout){
		cerr<<"Fail to create the data printout file: "
		    <<file_path<<endl;
	}
	else{
//		cout<<"start debugging..."<<endl;
		for(int i = 0; i<buffer_output_; i++){
			char Hex_out[5];
			_uint8ToHex(buffer[i],Hex_out);
//			cout<<_uint8ToHex(buffer[buffer_output_])<<" ";
			printout<<Hex_out;
		}
//		cout<<"end debugging..."<<endl;
	}
	printout.close();

/*
	cout<<"C40 Request - set up the command channel:"<<endl;
	Command_line cmd40("40","00",command_num,"response",sessionId,data);
	_write(req_server_.messenger_, cmd40);

	cout<<"C40 Action - openning a command channel "<<cmd_chan_
	    <<" to device "<<nn_addr_<<"..."<<endl;
	
	cmd_server_._initial(cmd_chan_);
	if(cmd_server_.Exit<0){
		cout<<"Couldn't connect to the NIC command channel "
		    <<cmd_chan_<<" ..."<<endl;
		return false;
	}
	cout<<"NNIC command channel initialized, ready to command!"<<endl;
	cmdChanPort_open_ = true;
	return true;
*/
}

void n_nic::_loopTerminal(void){

	bool flag = 1;
	while(flag){
		cout<<"Type in 1 for Entering command terminal 1\n";
		cout<<"Type in 2 for Entering command terminal 2\n";
		int terminal_;
		cin>>terminal_;
		if(terminal_ == 1)_loopTerminal_a1();
		if(terminal_ == 2)_loopTerminal_a2();
		cout<<"Type in 0 to terminate the program, 1 to continue: ";
		cin>>flag;
	}
	_nic_close();
}


void n_nic::_loopTerminal_a1(void){
	char command_[13][64];
	strcpy(command_[0],"DeviceInfo");
	strcpy(command_[1],"CmdChanPort");
	strcpy(command_[2],"AttachDataChanPort");
	strcpy(command_[3],"DetachDataChanPort");
	strcpy(command_[4],"InitPorts");
	strcpy(command_[5],"CreateGPRPort");
	strcpy(command_[6],"InitPortProtocol");
	strcpy(command_[7],"SendFromBuffer");
	strcpy(command_[8],"DataAcquisition");
	strcpy(command_[9],"DataStamp");
	strcpy(command_[10],"GetPortDeviceUID");
	strcpy(command_[11],"GetPortProtocolParamDef");
	cout<<"Type in the number of command to be executed."<<endl;
	for(int i = 0; i<12; i++){
		cout<<"command "<<dec<<i+1<<": "<<command_[i]<<endl;
	}
	int option_;
	cin>>option_;
	option_--;
	switch(option_){
		case 0: 
			cout<<"Type in the UID of device you want to know:";
			char input0[13];
			cin>>input0;
			_DeviceInfo(input0);
			break;
		case 1: 
			if(cmdChanPort_open_){
				cout<<"The command channel has been set to "
				    <<cmd_chan_<<endl;
				break;
			}
			else{
				cout<<"Executing CmdChanPort..."<<endl;
				_CmdChanPort();
				break;
			}
		case 2:
			cout<<"Type in the option for data channel to be attached:"
			    <<"\n1.listen\t2.transmit\t3.auto:";
			int input2;
			cin>>input2;
			if(input2 == 1)_AttachDataChanPort("listen");
			else if(input2 == 2)_AttachDataChanPort("transmit");
			else if(input2 == 3)_AttachDataChanPort("auto");
			break;
		case 3:
			cout<<"Detaching the data channel with mode "<<dataChanMode_
			    <<" right now..."<<endl;
			_DetachDataChanPort();
			break;
		case 4:
			cout<<"The list of ports have been initialized beginning with "
			    <<aa_addr_<<endl;
			cout<<"Type in the address to begin the initialization of NNIC ports: ";
			char input4[5];
			cin>>input4;
			cout<<"Executing InitPorts command"<<endl;
			_InitPorts(input4);
			break;
		case 5:
			cout<<"The GPR port has been created in "<<gpr_port_<<endl;
			cout<<"Type in the address of the GPR port to be created: ";
			char input5[5];
			cin>>input5;
			cout<<"Creating a GPR port as requested..."<<endl;
			_CreateGPRPort(input5);
			break;
		case 6:
			cout<<"There are total of "<<dec<<n_params<<" GPR port protocol stored, type in the index of the protocol to be initialized:";
			int input6;
			cin>>input6;
			cout<<"Initiating the protocol as requested."<<endl;
			_InitPortProtocol(input6);
			break;
		case 7:
			cout<<"Type in the length of data packet to be sent from the buffer:";
			signed long input7;
			cin>>input7;
			cout<<"Executing the command SendFromBuffer..."<<endl;
			_SendFromBuffer(input7);
			break;
		case 8:
			cout<<"Type in the option for data acquisition:"<<endl;
			cout<<"-- 1.start\t2.stop\t3.auto\t4.check: ";
			int input8;
			cin>>input8;
			if(input8 == 1){
				cout<<"starting data acquisition..."<<endl;
				_DataAcquisition("start");
			}
			else if(input8 == 2){
				cout<<"stopping data acquisition..."<<endl;
				_DataAcquisition("stop");
			}
			else if(input8 == 3){
				cout<<"starting data acquisition with auto mode..."<<endl;
				_DataAcquisition("auto");
			}
			else if(input8 == 4){
				cout<<"checking data acquisition mode..."<<endl;
				_DataAcquisition("check");
			}
			break;
		case 9:
			cout<<"Executing DataStamp command - reading from data channel..."<<endl;
			_DataStamp();
			break;
		case 10:
			cout<<"Type in the address of the port wanted for UID:";
			char input10[5];
			cin>>input10;
			cout<<"Requesting the UID of port "<<input10<<" ..."<<endl;
			_GetPortDeviceUID(input10);
			break;
		case 11:
			cout<<"Type in the address of the device wanted for protocol:(GPR port address: "<<gpr_port_<<" ) ";
			char input11_a[5];
			cin>>input11_a;
			cout<<"Type in the index of protocol parameter wanted for device "<<input11_a<<" : ";
			int input11_b;
			cin>>input11_b;
			cout<<"Requesting the "<<input11_b<<"th protocol parameter of device port "<<input11_a<<" ..."<<endl;
			_GetPortProtocolParamDef(input11_a,input11_b);
		default:
			cout<<"Command number entered is out of bound."<<endl;
			break;
	}
}

void n_nic::_loopTerminal_a2(void){
	char command_[13][64];
	strcpy(command_[0],"readAllDeviceInfo");
	strcpy(command_[1],"readAllDeviceUID");
	strcpy(command_[2],"readAllDefaultParam");
	strcpy(command_[3],"readParamFromFile");
	strcpy(command_[4],"setAllParam");
	cout<<"Type in the number of command to be executed."<<endl;
	for(int i = 0; i<5; i++){
		cout<<"command "<<dec<<i+1<<": "<<command_[i]<<endl;
	}
	int option_;
	cin>>option_;
	option_--;
	switch(option_){
		case 0: 
			cout<<"Reading all device info..."<<endl;
			_readAllDeviceInfo();
			break;
		case 1: 
			cout<<"Reading all device UID..."<<endl;
			_readAllDeviceUID();
			break;
		case 2:
			cout<<"Reading all default param from the device..."<<endl;
			cout<<"--option 1.save the parameter to file"<<endl;
			cout<<"--option 2.reading without saving it to file"<<endl;
			cout<<"Type in 1 or 2 to start reading: ";
			int input2;
			cin>>input2;
			if(input2==1)_readAllDefaultParam("save");
			if(input2==2)_readAllDefaultParam("discard");
			break;
		case 3:
			cout<<"Reading all parameters from the folder ~/Desktop/Param"<<endl;
			cout<<"-- there are two source of parameters to read in: 1. single file, 2. multiple files"<<endl;
			cout<<"Type in 1 or 2 to choose the source for reading in the parameters"<<endl;
			int input3;
			cin>>input3;
			if(input3==1)_readParamFromFile("single");
			if(input3==2)_readParamFromFile("multiple");
			break;
		case 4:
			cout<<"Initializing all parameters..."<<endl;
			cout<<"-- there are two source of parameters:\n 1.single file  2. multiple file  3.default"<<endl;
			cout<<"Type in 1, 2 or 3 to choose the source for setting all the parameters: ";
			int input4;
			cin>>input4;
			if(input4==1)_setAllParam("single");
			if(input4==2)_setAllParam("multiple");
			if(input4==3)_setAllParam("default");
			break;
		default:
			cout<<"Command number entered is out of bound."<<endl;
			break;
	}

}

bool n_nic::_CmdChanPort(void){

	char* command_num = "40";
	char* Err_type = "00";
	char d_channel[10];
	char data[16];
	_num2string(cmd_chan_, 4,d_channel); 
	strcpy(data,Err_type);
	strcat(data,nn_addr_);
	strcat(data,d_channel);

	//read from the request connection socket
	size_t real_size;
	real_size = _read(req_server_.messenger_, buffer, buf_size);

	cout<<"\nC40 Prereading - NIC on the connection request channel: "<<endl;
	for(int i =10; i<real_size; i++){
		cout<<(char)buffer[i];
	}
	cout<<"\n"<<endl;

	cout<<"C40 Request - set up the command channel:"<<endl;
	Command_line cmd40("40","00",command_num,"response",sessionId,data);
	_write(req_server_.messenger_, cmd40);

	cout<<"C40 Action - openning a command channel "<<cmd_chan_
	    <<" to device "<<nn_addr_<<"..."<<endl;
	
	cmd_server_._initial(cmd_chan_);
	if(cmd_server_.Exit<0){
		cout<<"Couldn't connect to the NIC command channel "
		    <<cmd_chan_<<" ..."<<endl;
		return false;
	}
	cout<<"NNIC command channel initialized, ready to command!"<<endl;
	cmdChanPort_open_ = true;
	return true;
}

void n_nic::_InitPorts(char* input){

	char* command_num = "47";
	char data[16];
	strcpy(data,input);

	cout<<"\nC47 Request - Request a list of ports:"<<endl;
	Command_line cmd47(nn_addr_,"00",command_num,"request",sessionId,data);
	_write(cmd_server_.messenger_, cmd47);

	//read from the list of initPorts
	size_t real_size;
	real_size = _read(cmd_server_.messenger_, buffer, buf_size);
	int Err_ = buffer[10];
	if(Err_==0){
		cout<<"C47 Response - initPorts succeeded!"<<endl;
		n_ports = (real_size-11)/7;
		string GPR_ = "GPR@@@";
		for(int i = 0; i<n_ports; i++){
			char port_addr[5];
			char port_uid[8];
			stringstream ssm_, ssm2_;
			ssm_<<hex<<(int)buffer[11+7*i];
			ssm_>>nic_port_addr[i];
			ssm2_<<buffer[12+7*i]<<buffer[13+7*i]
			     <<buffer[14+7*i]<<buffer[15+7*i]
			     <<buffer[16+7*i]<<buffer[17+7*i];
			ssm2_>>nic_port_uid[i];
			cout<<"-- Port"<<nic_port_addr[i]<<": "
			    <<nic_port_uid[i]<<endl;
			if(GPR_.compare(nic_port_uid[i])==0){
				strcpy(gpr_port_, nic_port_addr[i]);
			}
		}
	}
	else{
		cout<<"C47 Response - initPorts failed!"<<endl;
	}
	cout<<"GPR port addr: "<<gpr_port_<<endl;

}

void n_nic::_DeviceInfo(char* input){

	char* command_num = "63";
	char data[16];
//	strcpy(data,nic_port_uid[port_i]);
	strcpy(data,input);

	cout<<"\nC63 Request - request device info of a known address "
	    <<input<<"."<<endl;
	Command_line cmd63(nn_addr_,"00",command_num,"request",sessionId,data);
	_write(cmd_server_.messenger_, cmd63);

	//response from DeviceInfo
	size_t real_size;
	real_size = _read(cmd_server_.messenger_, buffer, buf_size);
	int Err_ = buffer[10];
	if(Err_==0){
		cout<<"C63 Response - No error."<<endl;
		int Mm_ = buffer[11];
		if(Mm_ == 1){
			cout<<"-- Info acquired: "<<endl;
			for(int i = 12; i<real_size; i++){
				cout<<buffer[i];
			}
			cout<<"-- Info report done."<<endl;
		}
	}
	else if(Err_ == 1){
		cout<<"C63 Response - unspecified error"<<endl;
	}
	else if(Err_ == 2){
		cout<<"C63 Response - unknown device UID"<<endl;
	}
	else if(Err_ == 3){
		cout<<"C63 Response - device not detected"<<endl;
	}
	else if(Err_ == 4){
		cout<<"C63 Response - device doesn't supply information"<<endl;
	}
	

}

void n_nic::_readAllDeviceInfo(void){

	for(int port_i=0; port_i<n_ports; port_i++){
		_DeviceInfo(nic_port_uid[port_i]);
	}
}

void n_nic::_CreateGPRPort(char* input){

	char* command_num = "48";
	char data[16];
	strcpy(data,input);
	strcat(data,"00");

	cout<<"\nC48 Request - Create a virtual GPR port "<<gpr_port_<<":"<<endl;
	Command_line cmd48(nn_addr_,"00",command_num,"request",sessionId,data);
	_write(cmd_server_.messenger_, cmd48);

	//response from CreateGPRPort
	size_t real_size;
	real_size = _read(cmd_server_.messenger_, buffer, buf_size);
	int Err_ = buffer[10];
	if(Err_==0){
		cout<<"C48 Response - successful creation of GPR port"<<endl;
		cout<<"-- hardware ports used by the GPR port: ";
		for(int i = 11; i<real_size; i++){
			cout<<hex<<(int)buffer[i]<<" ";
		}
		cout<<"\n";
	}
	else if(Err_ == 1){
		cout<<"C48 Response - unspecified error"<<endl;
	}
	else if(Err_ == 2){
		cout<<"C48 Response - unknown radar type"<<endl;
	}
	else if(Err_ == 3){
		cout<<"C48 Response - invalid parameter for type"<<endl;
	}

}

void n_nic::_AttachDataChanPort(char* option){

	char* command_num = "41";
	char data[16];
	char d_channel[10];
	_num2string(data_chan_, 4,d_channel); 
	strcpy(data,gpr_port_);
	strcat(data,d_channel);

	string listen_ = "listen";
	string speak_ = "speak";
	string auto_ = "auto";

	if(listen_.compare(option)==0)strcat(data,"00");
	if(speak_.compare(option)==0)strcat(data,"01");
	if(auto_.compare(option)==0)strcat(data,"03");

	cout<<"\nC41 Request - Attach GPR port "<<gpr_port_
	    <<" to data channel "<<dec<<data_chan_<<":"<<endl;
	Command_line cmd41(nn_addr_,"00",command_num,"request",sessionId,data);
	_write(cmd_server_.messenger_, cmd41);

	//initial data server
	data_server_._initial(data_chan_);

	//response from AttachDataChanPort
	size_t real_size;
	real_size = _read(cmd_server_.messenger_, buffer, buf_size);
	int Err_ = buffer[10];
	if(Err_==0){
		cout<<"C41 Response - Data channel connection established."<<endl;
		strcpy(dataChanMode_, option);
		dataChanPort_open_ = true;
	}
	else if(Err_ == 1){
		cout<<"C41 Response - unspecified error"<<endl;
	}
	else if(Err_ == 2){
		cout<<"C41 Response - device address "<<gpr_port_
		    <<" not assigned."<<endl;
	}

}

void n_nic::_DetachDataChanPort(void){

	char option[8];
	strcpy(option, dataChanMode_);
	char* command_num = "42";
	char data[16];
	char d_channel[10];
	_num2string(data_chan_, 4,d_channel); 
	strcpy(data,gpr_port_);
	strcat(data,d_channel);
	string listen_ = "listen";
	string speak_ = "speak";
	string auto_ = "auto";

	if(listen_.compare(option)==0)strcat(data,"00");
	if(speak_.compare(option)==0)strcat(data,"01");
	if(auto_.compare(option)==0)strcat(data,"03");

	cout<<"\nC42 Request - Detach GPR port "<<gpr_port_
	    <<" to data channel "<<dec<<data_chan_<<":"<<endl;
	Command_line cmd42(nn_addr_,"00",command_num,"request",sessionId,data);
	_write(cmd_server_.messenger_, cmd42);

	//initial data server
	data_server_.s_close();

	//response from AttachDataChanPort
	size_t real_size;
	real_size = _read(cmd_server_.messenger_, buffer, buf_size);
	int Err_ = buffer[10];
	if(Err_==0){
		cout<<"C42 Response - Data channel connection detached."<<endl;
		dataChanPort_open_ = false;
	}
	else if(Err_ == 1){
		cout<<"C42 Response - unspecified error"<<endl;
	}
	else if(Err_ == 2){
		cout<<"C42 Response - device address "<<gpr_port_
		    <<" not assigned."<<endl;
	}

}
void n_nic::_printData(uint8_t* data){
        size_t size = data[3]*256*256*256+ data[2]*256*256 + data[1]*256 + data[0];

        cout<<"\n-------DATA PRINTING:-------\n";
        cout<<"****************************\n";
        cout<<"Message size: \t"<<dec<<size<<endl;
        cout<<"Message for: \t"<<hex<<(int)data[4]<<endl;
        cout<<"Message from :\t"<<hex<<(int)data[5]<<endl;
        cout<<"Command #: \t"<<hex<<(int)data[6]<<endl;
        cout<<"Message type: \t"<<hex<<(int)data[7]<<endl;
        cout<<"Session Id: \t"<<hex<<(int)data[9]<<(int)data[8]<<endl;
        cout<<"---------------\n";
        cout<<"CONTENT CARRIED :(In text) "<<endl;
        for(int i = 10; i<size; i++){
                cout<<(char)data[i];
        }
        cout<<"\nDone"<<endl;
        cout<<"---------------\n";
        cout<<"CONTENT CARRIED :(In hex) "<<endl;
        for(int i = 10; i<size; i++){
                cout<<hex<<(int)data[i]<<" ";
        }
        cout<<"\nDone"<<endl;
        cout<<"****************************\n"<<endl;

}

void n_nic::_readParamFromFile(char* option){

	string single_ = "single";
	string multiple_ = "multiple";

	if(single_.compare(option)==0){
		string file_path = file_folder_+"ParameterList.txt";
		streampos begin, end;
		ifstream infile(file_path.c_str(), ios::binary);
		begin = infile.tellg();
		infile.seekg(0, ios::end);
		end = infile.tellg();
		infile.close();
		size_t param_size = end-begin;

		infile.open(file_path.c_str());
		char temp[1024];
		char param_file_[1024];
		if(!infile.fail()){
			cout<<"Reading parameter lists from "<<file_path<<endl;
			string line;
			int flag = 1;
			while(getline(infile,line)){
				line.copy(temp, line.length(),0);
				temp[line.length()] = 0;
				if(flag == 1){
					strcpy(param_file_, temp);
					flag = 0;
				}
				else{
					strcat(param_file_,"\n");
					strcat(param_file_,temp);
				}
				char tempHeader[10];
				strncpy(tempHeader,temp,6);
				tempHeader[6]=0;
				if(strcmp(tempHeader, "SMPINT")==0){
					int i = 0;
					char tempData[16];
					while(temp[i+7]!=0){
						tempData[i] = temp[i+7];
						i++;
					}
					tempData[i] = 0;
					sampleInterval_ = tempData;
				}
				if(strcmp(tempHeader, "FREQ@@")==0){
					int i = 0;
					char tempData[16];
					while(temp[i+7]!=0){
						tempData[i] = temp[i+7];
						i++;
					}
					tempData[i] = 0;
					frequency_ = tempData;
				}
				
			}
			memcpy(gpr_param_list[0], param_file_, param_size);
			cout<<"Param list: "<<endl;
			cout<<gpr_param_list[0]<<endl;
			_hex2string(gpr_param_list[0], param_size, gpr_param_char[0]);
			strcat(gpr_param_char[0],"00");
			n_params = 1;
		}
		else{
			cout<<"Fail to open the input file "<<file_path<<endl;
		}

	}
	else if(multiple_.compare(option)==0){
		for(int param_i = 0; param_i<20; param_i++){
			string file_name;
			stringstream convert_;
			convert_<<param_i;
			file_name = convert_.str();
			string file_path = file_folder_+"index_"+file_name+".txt";
			streampos begin, end;
			ifstream infile(file_path.c_str(), ios::binary);
			begin = infile.tellg();
			infile.seekg(0, ios::end);
			end = infile.tellg();
			infile.close();
			size_t param_size = end-begin;

			infile.open(file_path.c_str());
			char temp[1024];
			char param_file_[1024];
			if(!infile.fail()){
				cout<<"Reading param index "<<param_i<<" from "<<file_path<<endl;
				string line;
				int flag = 1;
				while(getline(infile, line)){
					line.copy(temp, line.length(),0);
					temp[line.length()]=0;
					if(flag == 1){
						strcpy(param_file_,temp);
						flag = 0;
					}
					else{
						strcat(param_file_,"\n");
						strcat(param_file_,temp);
					}
				}
				memcpy(gpr_param_list[param_i],param_file_,param_size);
			
				cout<<"Param index "<<param_i<<": "<<endl;
				cout<<gpr_param_list[param_i]<<endl;
				_hex2string(gpr_param_list[param_i], param_size, gpr_param_char[param_i]);
				strcat(gpr_param_char[param_i],"00");
			}
			else{
				cout<<"Fail to open the input file "<<file_path<<endl;
				n_params = param_i;
				break;
			}
			infile.close();
		}
	}

}

void n_nic::_InitPortProtocol(int param_i){

	char* command_num = "49";
	char data[1024];
	strcpy(data,gpr_port_);
	strcat(data,gpr_param_char[param_i]);

	cout<<"\nC49 Request - initialize gpr port protocol parameter of index "
	    <<dec<<param_i<<endl;
	Command_line cmd49(nn_addr_,"00",command_num,"request",sessionId,data);
	_write(cmd_server_.messenger_, cmd49);

//debugging
	uint8_t test[1024];
	cmd49._char2hex(gpr_param_char[param_i],test);
	cout<<"as:--------------------\n"<<test<<"\n--------------------"<<endl;
//	cout<<"Checking command...\n"<<endl;
//	for(int i = 0; i<cmd49.size; i++){
//		cout<<hex<<(int)cmd49.cmd_line[i]<<" ";
//	}
//	cout<<"\nDone checking...\n"<<endl;
//debugging

	//response from GetPortProtocolParamDef
	size_t real_size;
	real_size = _read(cmd_server_.messenger_, buffer, buf_size);
	cout<<"Buffer 0-9:"<<endl;
	for(int i = 0; i<10; i++)cout<<hex<<(int)buffer[i]<<" ";
	cout<<endl;
	int Err_ = buffer[10];
	if(Err_==0){
		cout<<"C49 Response - Initialized Okay."<<endl;
	}
	else if(Err_ == 1){
		cout<<"C49 Response - unspecified error"<<endl;
	}
	else if(Err_ == 2){
		cout<<"C49 Response - invalid device address (not assigned)"<<endl;
	}
	else if(Err_ == 3){
		cout<<"C49 Response - device doesn't support command"<<endl;
	}
	else if(Err_ == 4){
		cout<<"C49 Response - failed initialization"<<endl;
	}
	else if(Err_ == 5){
		cout<<"C49 Response - device not initialized (can't respond with its protocol string)"<<endl;
	}
	else if(Err_ == 6){
		cout<<"C49 Response - not compatible device (most probably firmware update is required)"<<endl;
	}
	else if(Err_ == 7){
		cout<<"C49 Response - values of interdependent parameters combine to give invalid result"<<endl;
		cout<<"-- Info acquired: "<<endl;
		for(int i = 11; i<real_size; i++){
			cout<<buffer[i];
		}
		cout<<"-- Info report done."<<endl;
	}
//debugging
	_GetPortProtocolParamDef(gpr_port_, param_i);
//debugging
}

void n_nic::_setAllParam(char* option){

	string single_ = "single";
	string multiple_ = "multiple";
	string default_ = "default";
	if(single_.compare(option)==0){
		_readParamFromFile(option);
	}
	else if(multiple_.compare(option)==0){
		_readParamFromFile(option);
	}
	else if(default_.compare(option)==0){
		_readAllDefaultParam("save");
	}
	for(int i = 0; i<n_params; i++){
		_InitPortProtocol(i);
	}

}

int n_nic::_GetPortProtocolParamDef(char* dev_addr_, int param_i){

	char* command_num = "62";
	char data[16];
	char param_index[8];
	_num2string(param_i, 4, param_index);
	strcpy(data,dev_addr_);
	strcat(data,param_index);

	cout<<"\nC62 Request - get gpr port protocol parameter of index "
	    <<dec<<param_i<<endl;
	Command_line cmd62(nn_addr_,"00",command_num,"request",sessionId,data);
	_write(cmd_server_.messenger_, cmd62);

	//response from GetPortProtocolParamDef
	size_t real_size;
	real_size = _read(cmd_server_.messenger_, buffer, buf_size);
	int Err_ = buffer[10];
	if(Err_==0){
		cout<<"C62 Response - Device Identified."<<endl;
		cout<<"-- parameter acquired: "<<endl;
		for(int i = 12; i<real_size; i++){
			gpr_param_list[param_i][i-12] = buffer[i];
		}
		cout<<gpr_param_list[param_i]<<endl;	
		cout<<"-- parameter report done."<<endl;
	}
	else if(Err_ == 1){
		cout<<"C62 Response - unspecified error"<<endl;
	}
	else if(Err_ == 2){
		cout<<"C62 Response - device address not assigned"<<endl;
	}
	else if(Err_ == 3){
		cout<<"C62 Response - no device detected (not necessarily no device)"<<endl;
	}
	else if(Err_ == 4){
		cout<<"C62 Response - no device"<<endl;
	}
	else if(Err_ == 5){
		cout<<"C62 Response - unknown device"<<endl;
	}
	else if(Err_ == 6){
		cout<<"C62 Response - parameter index out of bounds"<<endl;
	}
	
	return Err_;
}

void n_nic::_readAllDefaultParam(char* option){

	string save_ = "save";
	string discard_ = "discard";
	for(int param_i = 0; param_i<20; param_i++){
		if(_GetPortProtocolParamDef(gpr_port_, param_i)!=0){
			n_params=param_i;
			break;
		}
		if(save_.compare(option)==0){// saving parameter list into files
			string file_name;
			stringstream convert_;
			convert_<<param_i;
			file_name = convert_.str();
			string file_path = "/home/kexiao/Desktop/Param/index_"+file_name+".txt";
			ofstream outfile;
			outfile.open(file_path.c_str());
			if(!outfile.fail()){
				cout<<"saving param index "<<param_i<<" into "<<file_path<<endl;
			}
			else{
				cout<<"Fail to create the output file for parameter list"<<endl;
			}
			outfile<<gpr_param_list[param_i];
			outfile.close();
		}//finish saving files
		_hex2string(gpr_param_list[param_i], strlen(gpr_param_list[param_i]), gpr_param_char[param_i]);
		strcat(gpr_param_char[param_i],"00");
	}
}

void n_nic::_GetPortDeviceUID(char* input){

	char* command_num = "61";
	char data[16];
	strcpy(data,input);

	cout<<"\nC61 Request - request UID of a SSI device on port "
	    <<input<<"."<<endl;
	Command_line cmd61(nn_addr_,"00",command_num,"request",sessionId,data);
	_write(cmd_server_.messenger_, cmd61);

	//response from GetPortDeviceUID
	size_t real_size;
	real_size = _read(cmd_server_.messenger_, buffer, buf_size);
	int Err_ = buffer[10];
	if(Err_==0){
		cout<<"C61 Response - Device Identified."<<endl;
		cout<<"-- Info acquired: ";
		for(int i = 11; i<real_size; i++){
			cout<<buffer[i];
		}
		cout<<"\n-- Info report done."<<endl;
	}
	else if(Err_ == 1){
		cout<<"C61 Response - unspecified error"<<endl;
	}
	else if(Err_ == 2){
		cout<<"C61 Response - device address not assigned"<<endl;
	}
	else if(Err_ == 3){
		cout<<"C61 Response - no device detected (not necessarily no device)"<<endl;
	}
	else if(Err_ == 4){
		cout<<"C61 Response - no device"<<endl;
	}
	else if(Err_ == 5){
		cout<<"C61 Response - unknown device"<<endl;
	}
	

}

void n_nic::_DataAcquisition(char* action){

	char* command_num = "50";
	char data[16];

	string start_ = "start";
	string stop_ = "stop";
	string auto_ = "auto";
	string check_ = "check";
	int choice_;
	if(stop_.compare(action)==0){
		choice_ = 0;
		cout<<"\nC50 Request - stop data acquisition"<<endl;
	}
	if(start_.compare(action)==0){
		choice_ = 1;
		cout<<"\nC50 Request - start data acquisition"<<endl;
	}
	if(auto_.compare(action)==0){
		choice_ = 2;
		cout<<"\nC50 Request - start data acquisition, auto stop after 1 data chunk"<<endl;
	}
	if(check_.compare(action)==0){
		choice_ = 255;
		cout<<"\nC50 Request - request current mode and status of data acquisition"<<endl;
	}
	
	char Mm_[8];
	_num2string(choice_, 2, Mm_);
	strcpy(data,Mm_);

	Command_line cmd50(gpr_port_,"00",command_num,"request",sessionId,data);
	_write(cmd_server_.messenger_, cmd50);

	//response from DataAcquisition
	size_t real_size;
	real_size = _read(cmd_server_.messenger_, buffer, buf_size);
	int Err_ = buffer[10];

	if(Err_==0){
		cout<<"C50 Response - action succeed."<<endl;
	}
	else if(Err_ == 1){
		cout<<"C50 Response - unspecified error"<<endl;
	}
	else if(Err_ == 2){
		if(choice_ == 1){
			cout<<"C50 Response - can't start as requested, already started"<<endl;
		}
		else if(choice_ == 0){
			cout<<"C50 Response - can't stop as requested, already stopped"<<endl;
			
		}
	}
	else if(Err_ == 3){
		cout<<"C50 Response - NIC ports not setup / initialized / failed"<<endl;
	}
	else if(Err_ == 4){
		cout<<"C50 Response - radar is off"<<endl;
	}
	else if(Err_ == 5){
		cout<<"C50 Response - radar not initialized"<<endl;
	}
	else if(Err_ == 6){
		cout<<"C50 Response - mode not supported by device"<<endl;
	}

	if(real_size == 13){
		// read the status report
		signed short ss_;
		ss_ = (buffer[12]<<8)|buffer[11];
		cout<<"C 50 Response - The current status report : "<<ss_<<endl;
		if(ss_>0){
			cout<<"-- Data acquisition : on"<<endl;
			dataAcquisition_start_ = true;
		}
		else if(ss_<0){
			cout<<"-- Data acquisition : off"<<endl;
			ss_ = ss_*-1;
			dataAcquisition_start_ = false;
		}
		else{
			cout<<"-- Data acquisition : no mode"<<endl;
		}

		if(ss_ == 1){
			cout<<"-- Mode : Odom"<<endl;
		}
		else if(ss_ == 2){
			cout<<"-- Mode : Free_Odom"<<endl;
		}
		else if(ss_ == 3){
			cout<<"-- Mode : Free_Run"<<endl;
		}
		else if(ss_ == 4){
			cout<<"-- Mode : Trigger"<<endl;
		}
	}
}

size_t n_nic::_SendFromBuffer(signed long rr_){

	char* command_num = "4B";
	char data[16];

	char len_[4];
	len_[0] = rr_&0xFF;
	len_[1] = (rr_>>8)&0xFF;
	len_[2] = (rr_>>16)&0xFF;
	len_[3] = (rr_>>24)&0xFF;
	
	_hex2string(len_,4,data);

	if(rr_<0){
		cout<<"\nC4B Request - self initiate send on data channel whenever buffer has "<<-rr_<<" bytes of data"<<endl;
	}
	if(rr_==0){
		cout<<"\nC4B Request - stop self initiate send"<<endl;
	}
	if(rr_>0){
		cout<<"\nC4B Request - request "<<rr_<<" bytes of data from buffer"<<endl;
	}

	Command_line cmd4B(gpr_port_,"00",command_num,"request",sessionId,data);
	_write(cmd_server_.messenger_, cmd4B);

	//response from SendFromBuffer
	size_t real_size;
	real_size = _read(cmd_server_.messenger_, buffer, buf_size);
	int Err_ = buffer[10];

	signed long ll_, pp_;
	ll_ = (buffer[14]<<24)|(buffer[13]<<16)|(buffer[12]<<8)|buffer[11];
	pp_ = (buffer[18]<<24)|(buffer[17]<<16)|(buffer[16]<<8)|buffer[15];


	if(Err_ == 0){
		cout<<"C4B Response - action succeed"<<endl;
		if(rr_<=0){
			cout<<"-- current buffer byte count: "
			    <<dec<<ll_<<endl;
		}
		if(rr_>0){
			cout<<"-- "<<dec<<ll_<<" bytes of data will be send from buffer"<<endl;
			cout<<"-- "<<dec<<pp_<<" bytes of data will be left on buffer"<<endl;
			buffer_output_ = ll_;
		}
	}
	else if(Err_ == 1){
		cout<<"C4B Response - unspecified error"<<endl;
	}
	else if(Err_ == 2){
		cout<<"C4B Response - invalid device address (not assigned)"<<endl;
	}

	return (size_t)ll_;
}

void n_nic::_readAllDeviceUID(void){

	for(int i = 0; i<n_ports; i++){
		_GetPortDeviceUID(nic_port_addr[i]);
	}
}

void n_nic::_write(int _msger, Command_line cmd){
	send(_msger,cmd.cmd_line,cmd.size,0);
	_get_sessionId();
}

size_t n_nic::_read(int _msger, uint8_t* input, size_t input_bufSize){
        recv(_msger, input, input_bufSize, 0);
        size_t size = input[3]*256*256*256+ input[2]*256*256 + input[1]*256 + input[0];
	return size;
}

void n_nic::_num2string(int data, int len, char* output){

	size_t hex_l = len/2;
	int out1[hex_l];
	int out2[len];
	for(int i = hex_l-1; i>0; i--){
		out1[i] = data/256;
		data = data - out1[i]*256;
	}
	out1[0] = data;
	for(int i = 0; i<hex_l; i++){
		out2[2*i] = out1[i]/16;
		out2[2*i+1] = out1[i]-out2[2*i]*16;
	}
	for(int i = 0; i<len; i++){
		stringstream buf;
		buf<<hex<<out2[i];
		buf>>output[i];
	}
}


void n_nic::_get_sessionId(void){
	sessionId+=1;
	if(sessionId>65535){
		sessionId = 0;
	}
}

int n_nic::_string2num(char* data){

	int temp;
	int output = 0;
	size_t len = strlen(data)/2;
	for(int i = 0; i<len; i++){
		stringstream ssm_;
		ssm_<<data[i*2]<<data[i*2+1];
		ssm_>>hex>>temp;
		output += temp*pow(256,i);
	}
	return output;
}

void n_nic::_hex2string(char* in, size_t ss, char* output){


	size_t out_size = ss*2;
	char temp[5];
	char out[1024];
	for(int i = 0; i<ss; i++){
		stringstream ssm_;
		ssm_<<hex<<(int)in[i];
		ssm_>>temp;
		if(strlen(temp) == 1){
			out[2*i] = '0';
			out[2*i+1] = temp[0];
		}
		else{
			out[2*i] = temp[0];
			out[2*i+1] = temp[1];
		}
	}
	out[2*ss+2] = 0;
	strcpy(output,out);
}

void n_nic::_nic_close(void){

	if(dataAcquisition_start_){
		_DataAcquisition("stop");
	}
	if(dataChanPort_open_){ 
		_DetachDataChanPort();
	}
	if(data_server_.server_open_){ 
		data_server_.s_close();
	}
	if(cmd_server_.server_open_){ 
		cmd_server_.s_close();
		cmdChanPort_open_ = false;
	}
	if(req_server_.server_open_){ 
		req_server_.s_close();
	}

}

