


#ifndef NETWORK_PACKET_H
#define NETWORK_PACKET_H

#include<string>

#define BREAK_CHAR '|'
#define SEPERATE_CHAR ';'

enum KEYS {
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
    FUNNY
};



struct NetworkPacket{
    REQUEST code;
    KEYS key;
    std::string data;
};


NetworkPacket parser(std::string buffer) {
    NetworkPacket p;
    int seperateA = buffer.find(SEPERATE_CHAR);
    int seperateB = buffer.substr(0, seperateA).find(SEPERATE_CHAR);
    if (buffer.at(0) != BREAK_CHAR) {
        prgm_error("Parse Error\n");
        return p;
    }
    p.key = (KEYS)std::stoi(buffer.substr(1,seperateA));
    p.code = (REQUEST)std::stoi(buffer.substr(seperateA,seperateB));
    p.data = buffer.substr(seperateB, buffer.size());

    return p;
}

std::string stringBuilder(NetworkPacket p) {
    std::string out;
    out += BREAK_CHAR;
    out += std::to_string(p.key);
    out += SEPERATE_CHAR;
    out += std::to_string(p.code);
    out += SEPERATE_CHAR;
    out += p.data;
    out += SEPERATE_CHAR;
    return out;
}



#endif