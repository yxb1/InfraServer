#include "udp_sock.h"

UdpSock::UdpSock(SocketInfo info): socket_info(info){
    sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock_fd < 0) {
        std::cout << "Socket create fail - " << strerror(errno) << std::endl;
        exit(-1);
    }

    struct sockaddr_in bind_addr;
    memset(&bind_addr, 0, sizeof(bind_addr));
    if(!strcmp("server", socket_info.identify.c_str())) {
        bind_addr.sin_family = AF_INET;
        bind_addr.sin_port = htons(socket_info.ser_port);
        bind_addr.sin_addr.s_addr = inet_addr(socket_info.ser_ip.c_str());

        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(socket_info.cli_port);
        _addr.sin_addr.s_addr = inet_addr(socket_info.cli_ip.c_str());
    }
    else
    {
        bind_addr.sin_family = AF_INET;
        bind_addr.sin_port = htons(socket_info.cli_port);
        bind_addr.sin_addr.s_addr = inet_addr(socket_info.cli_ip.c_str());

        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(socket_info.ser_port);
        _addr.sin_addr.s_addr = inet_addr(socket_info.ser_ip.c_str());
    }

    int ret = bind(sock_fd, (sockaddr*)&bind_addr, sizeof(bind_addr));
    if(ret < 0) {
        std::cout << "Bind fail - " << strerror(errno) << std::endl;
        exit(-1);
    }
}

UdpSock::~UdpSock() {
    close(sock_fd);
}

void UdpSock::SocketSend(char *ptr, int ss_len) {
    static char s_buff[MAX_BUFF_LEN] = {0};
    static uint32_t session_id = 0;
    int s_len = 0;

    if(ss_len > MAX_BUFF_LEN) {
        std::cout << "Oversize when send, ss_len is " << ss_len << std::endl;
        exit(-1);
    }

    if(ptr == NULL) {
        std::cout << "ptr is nullptr when send." << std::endl;
        exit(-1);
    }
    else
    {
        memcpy(s_buff, ptr, ss_len);
    }

    int real_send = sendto(sock_fd, s_buff, ss_len, 0, (struct sockaddr *)&_addr, sizeof(_addr));
    if(real_send < 0) {
        std::cout << "real_send is " << real_send << ". " << strerror(errno) << std::endl;
    }
    else
    {
        std::cout << "real_send is " << real_send << std::endl;
    }
}

int UdpSock::SocketRecv(char *ptr, int &rr_len) {
    static char r_buff[MAX_BUFF_LEN] = {0};
    struct sockaddr_in src_addr;
	socklen_t src_addr_len = 0;

    if(ptr == NULL) {
        std::cout << "Buffer point is NULL when receive data." << std::endl;
        exit(-1);
    }

    int r_len = recvfrom(sock_fd, r_buff, MAX_BUFF_LEN, 0, (sockaddr*)&src_addr, &src_addr_len);
    if(r_len < 0) {
        std::cout << "real_recv is " << r_len << ". " << strerror(errno) << std::endl;
        return -1;
    }
    else
    {
        memcpy(ptr, r_buff, r_len);
        rr_len = r_len;
        return r_len;
    }
}
