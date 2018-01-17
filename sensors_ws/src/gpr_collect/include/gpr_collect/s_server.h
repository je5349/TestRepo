#ifndef S_SERVER_H
#define S_SERVER_H

#include <netinet/in.h>
#include <stdint.h>
#include <stdlib.h>
#include "gpr_collect/command_line.h"


class s_server
{
public:
	s_server(void);

	void _initial(int);
	void SetPortNum(int);
	int Server_initial(void);
	int Server_accept(void);
	void Server_read(uint8_t*, size_t);
	void Server_write(uint8_t*, size_t);
	void buffer_read(void);
	void printData(uint8_t*);
	void s_close(void);

	int Exit = 0;
	const int buf_size_ = 1024;
	uint8_t buffer_[1024];
	size_t output_size_ = 1024;

	int messenger_;
	bool server_open_ = false;
private:
	int server_;
	int portNum;
	struct sockaddr_in server_addr, peer_addr;
	socklen_t peer_addr_size;
};


#endif
