#ifndef _INFRA_DATA_TYPE_H_
#define _INFRA_DATA_TYPE_H_

#include <string>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <unistd.h>
#include <stdio.h>

/******socket information for udp***/
struct SocketInfo {
    uint32_t ser_port;
    uint32_t cli_port;
    std::string ser_ip;
    std::string cli_ip;
    std::string identify;
};

/**********opponent status**********/
struct _OpponentStatus {
    uint8_t mcu_status;
    uint8_t tbox_status;
    uint8_t hut_status;
};
#endif
