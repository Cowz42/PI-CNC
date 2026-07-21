



#include"globalcommunication.h"

#include<vector>



std::vector<std::string> errArr;
std::vector<std::string> msgArr;



void pushError(std::string err) {
    errArr.push_back(err);
}


void pushMessage(std::string msg) {
    msgArr.push_back(msg);
}




std::string getMessage() {
    std::string msg = msgArr.at(msgArr.size() - 1);
    msgArr.pop_back();
    return msg;
}


std::string getError() {
    std::string err = errArr.at(errArr.size() - 1);
    errArr.pop_back();
    return err;
}



bool checkError() {
    return !errArr.empty();
}


bool checkMessage() {
    return !msgArr.empty();
}

