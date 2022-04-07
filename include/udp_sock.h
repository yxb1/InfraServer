#ifndef _UDP_SOCK_HEAD_
#define _UDP_SOCK_HEAD_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <memory.h>
#include <unistd.h>
#include <stdio.h>
#include "param.h"

#define MAX_BUFF_LEN (100*1024)

class UdpSock {
public:
    UdpSock(SocketInfo info);
    ~UdpSock();
    void SocketSend(char *ptr, int ss_len);
    int SocketRecv(char *ptr, int &rr_len);

private:
    int sock_fd;
    struct sockaddr_in _addr;
    SocketInfo socket_info;
};

#endif
