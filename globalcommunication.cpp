



#include"globalcommunication.h"

#include<vector>



vector<std::string> errArr;
vector<std::string> msgArr;



void pushError(std::string err) {
    errArr.push_back(err);
}


void pushMessage(std::string msg) {
    msgArr.push_back(msg);
}




std::string getMessage() {
    return msgArr.pop_back();
}


std::string getError() {
    return errArr.pop_back();;
}



bool checkError() {
    return !errArr.empty();
}


bool checkMessage() {
    return !msgArr.empty();
}

