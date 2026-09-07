



#include"globalcommunication.hpp"
#include"socketmanager.hpp"

#include<vector>
#include<iostream>
#include<fstream>

bool prgm_exit = false;


std::vector<std::string> prgmErrorArr;
std::vector<std::string> prgmLogArr;
std::vector<std::string> sysErrorArr;
std::vector<std::string> sysLogArr;



std::string logFileName;
std::string errorFileName;


std::ofstream logFile;
std::ofstream errorFile;

void mountLogFile(std::string name) {
    logFileName = name;
    logFile.open(logFileName);
}

void mountErrorFile(std::string name) {
    errorFileName = name;
    errorFile.open(errorFileName);
}

void prgm_error(std::string msg) {
    if (msg.substr(0,8) == "SYS_ERR:") {
        std::cerr << msg;
    } else {
        std::cerr << "ERR: " << msg;
    }
    if (errorFile.is_open()){
        errorFile << msg;
    }
    prgmErrorArr.push_back(msg);

}

void prgm_log(std::string msg) {
    if (msg.substr(0,8) == "SYS_LOG:") {
        std::cerr << msg;
    } else {
        std::cerr << "LOG: " << msg;
    }
    if (logFile.is_open()){
        logFile << msg;
    }
    prgmLogArr.push_back(msg);
}

void sys_error(std::string msg) {
    prgm_error("SYS_ERR: " + msg);
    prgmErrorArr.push_back(msg);
    net_socket.sendError(msg);
}

void sys_log(std::string msg) {
    prgm_log("SYS_LOG: " + msg);
    prgmLogArr.push_back(msg);
    net_socket.sendLog(msg);
}

void unMountFiles() {
    errorFile.close();
    logFile.close();
}