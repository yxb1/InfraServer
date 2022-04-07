#ifndef _OPPONENT_STATUS_HEAD_
#define _OPPONENT_STATUS_HEAD_

#include <string>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <unistd.h>

#include "param.h"
#include "udp_sock.h"

#define SYSTEM_RUN_RESULT(ret) ((ret != -1) && WIFEXITED(ret) && (WEXITSTATUS(ret) == 0))

class OpponentStatus {
public:
    OpponentStatus(UdpSock *udp);
    virtual ~OpponentStatus();
    void run();

private:
    _OpponentStatus oppnt_status;
    UdpSock *sock_udp;
    std::thread handle;
};

#endif
