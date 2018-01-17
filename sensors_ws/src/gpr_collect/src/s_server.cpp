#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <stdint.h>
#include <bitset>
#include "gpr_collect/s_server.h"


using namespace std;

s_server::s_server(void){

}

void s_server::_initial(int p_Num)
{
	SetPortNum(p_Num);
	if (Server_initial() < 0){
		cout<<"Error creating a server!"<<endl;
		Exit = -1;
	}
	else if(Server_accept() <0){
		cout<<"Error establish connection to client!"<<endl;
	}
	else{
		server_open_ = true;
	}
}

void s_server::SetPortNum(int p_Num){
	portNum = p_Num;
}


int s_server::Server_initial(void){
	// Create a server socket
	server_ = socket(AF_INET, SOCK_STREAM, 0);
	if (server_ < 0){
		cout<<"Error creating a server socket."<<endl;
		return -1;
	}

	// Set up the port number for the server socket
	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(portNum);

	// Binding the socket to the server_addr
	if (bind(server_, (struct sockaddr*) &server_addr, sizeof(server_addr)) <0){
		cout<<"Error binding the socket."<<endl;
		return -1;
	}

	// Listening socket
	if( listen(server_,1) < 0){
		cout<<"Error setting up the socket as a passive socket";
		return -1;
	}
	cout<<"The server has been initialized, ready to pair..."<<endl;
	return 0;
}

int s_server::Server_accept(void){
	// Accept client
	peer_addr_size = sizeof(server_addr);
	messenger_ = accept(server_, (struct sockaddr*) &peer_addr, &peer_addr_size);
	if (messenger_ < 0){
		cout<<"Error on accepting client..."<<endl;
		return -1;
	}
	cout<<"Server connected to client on port: "<<dec<<portNum<<endl;
	return 0;
}


void s_server::Server_read(uint8_t* input, size_t input_bufSize){
	recv(messenger_, input, input_bufSize, 0);
	printData(input);
//	printHex(input);
}

void s_server::buffer_read(void){
	recv(messenger_, buffer_, buf_size_, 0);
	cout<<"Done receiving..."<<endl;
	printData(buffer_);
}

void s_server::Server_write(uint8_t* output, size_t output_bufSize){
	send(messenger_, output, output_bufSize, 0);
}

/*
void S_server::printHex(uint8_t* data){
	size_t size = data[3]*256*256*256+ data[2]*256*256 + data[1]*256 + data[0];
	cout<<"Data printing as hex (size:"<<size<<"):\n";
	for(int i = 0; i<size; i++){
		cout<<hex<<(int)data[i]<<" ";
	}
	cout<<"\nDone\n"<<endl;
}
*/

void s_server::printData(uint8_t* data){
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

void s_server::s_close(void){
	close(server_);
	server_open_ = false;
}
