#ifndef _INFRA_SERVER_ERROR_LIST_
#define _INFRA_SERVER_ERROR_LIST_

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <unistd.h>
#include <stdio.h>

enum ErrNum {
    OPEN_FILE_FAIL = 0x01,
};

class ErrorList {
public:
    ErrorList() {
        err_map.insert(std::pair<uint32_t, std::string>(OPEN_FILE_FAIL, "Open file falled."));
        std::cout << "<ErrorList> " << "Enter constructor." << std::endl;
    }
    virtual ~ErrorList(){
        std::cout << "<ErrorList> " << "Enter destructor." << std::endl;
    }
    std::string GetErrMsg(uint32_t err_num){
        std::map<uint32_t, std::string>::iterator iter = err_map.find(err_num);
        if(iter != err_map.end()) {
            return iter->second;
        }
        else {
            std::cout << "<ErrorList> " << "Can't found error message. ErrNum = " << err_num << std::endl;
        }
    }

private:
    std::map<uint32_t, std::string> err_map;
};

#endif
