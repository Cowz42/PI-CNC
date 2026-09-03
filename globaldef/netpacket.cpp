


#include"netpacket.hpp"





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
    if (p.data.size() > 200) {
        out += p.data.substr(0, 200);
    } else {
        out += p.data;
    }
    out += SEPERATE_CHAR;
    return out;
}