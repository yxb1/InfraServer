#include <string.h>
#include "opponent.h"

OpponentStatus *status_ptr = NULL;
OpponentStatus::OpponentStatus(UdpSock *udp):sock_udp(udp) {
    memset(&oppnt_status, 0, sizeof(oppnt_status));
    handle = std::thread(&OpponentStatus::run, this);
    std::cout << "Enter OpponentStatus constructor." << std::endl;
}

OpponentStatus::~OpponentStatus() {
    std::cout << "Enter OpponentStatus destructor." << std::endl;
}

void OpponentStatus::run() {
    status_ptr = this;
    while(1) {
        int ret = system("ping -c 1 172.16.5.87");
        if(SYSTEM_RUN_RESULT(ret)) {
            printf("ping -c 1 172.16.5.87 success, ret = %d\n", ret);
            status_ptr->oppnt_status.mcu_status = 1;
        }
        else {
            printf("ping -c 1 172.16.5.87 fail, ret = %d\n", ret);
            status_ptr->oppnt_status.mcu_status = 0;
        }

        ret = system("ping -c 1 172.16.2.97");
        if(SYSTEM_RUN_RESULT(ret)) {
            printf("ping -c 1 172.16.2.97 success, ret = %d\n", ret);
            status_ptr->oppnt_status.tbox_status = 1;
        }
        else {
            printf("ping -c 1 172.16.2.97 fail, ret = %d\n", ret);
            status_ptr->oppnt_status.tbox_status = 0;
        }

        ret = system("ping -c 1 172.16.2.99");
        if(SYSTEM_RUN_RESULT(ret)) {
            printf("ping -c 1 172.16.2.99 success, ret = %d\n", ret);
            status_ptr->oppnt_status.hut_status = 1;
        }
        else {
            printf("ping -c 1 172.16.2.99 fail, ret = %d\n", ret);
            status_ptr->oppnt_status.hut_status = 0;
        }

        status_ptr->sock_udp->SocketSend((char *)&status_ptr->oppnt_status, sizeof(_OpponentStatus));
        sleep(1);
    }
}
