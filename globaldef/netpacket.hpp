


#ifndef NETWORK_PACKET_H
#define NETWORK_PACKET_H

#include<string>

#include"globalcommunication.hpp"

#define BREAK_CHAR '|'
#define SEPERATE_CHAR ';'

enum KEYS {
    NONE,
    X_P,
    Y_P,
    Z_P,
    A_P,
    B_P,
    C_B,
    R_S,
    F_N,
    L_S,
    E_S
};

enum REQUEST {
    VERSION,
    WRITE,
    READ,
    ERROR,
    LOG,
    FUNNY,
    ACK
};



struct NetworkPacket{
    REQUEST code;
    KEYS key;
    std::string data;
};

NetworkPacket parser(std::string buffer);

std::string stringBuilder(NetworkPacket p);



#endif