#include <string>
#include <iostream>
#include <sstream>
#include <memory>

#include "errorlist.h"
#include "opponent.h"
#include "param.h"
#include "udp_sock.h"

SocketInfo oppnt_sock_info = {
    62001,
    57001,
    "192.168.1.12",
    "192.168.1.10",
    "server"
};

int main(int argc, char ** argv) {
    std::cout << "Enter main" << std::endl;
    std::shared_ptr<OpponentStatus> _oppnt_status = std::make_shared<OpponentStatus>(new UdpSock(oppnt_sock_info));
    std::cout << "Create OpponentStatus finished" << std::endl;
    while(1) {
        sleep(10);
    }
    return 0;
}