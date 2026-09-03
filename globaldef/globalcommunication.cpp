



#include"globalcommunication.hpp"

#include<vector>



std::vector<std::string> errArr;
std::vector<std::string> msgArr;


void prgm_error(std::string msg) {
    prgm_error(msg.data());
}

void prgm_error(const char* msg) {
    
}

void prgm_log(std::string msg) {
    prgm_log(msg.data());
}

void prgm_log(const char* msg) {
    
}

void sys_error(std::string msg) {
    sys_error(msg.data());
}

void sys_error(const char* msg) {
    
}

void sys_log(std::string msg) {
    sys_log(msg.data());
}

void sys_log(const char* msg) {
    
}




bool checkError() {
    return !errArr.empty();
}


bool checkMessage() {
    return !msgArr.empty();
}

