

#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H


#include<string>

class Socket {
    public:
    static bool start();
    static void end();
    static void transmit(std::string msg);
    static void transmit(const char*);
    static std::string recieve();
};

extern Socket s;

#endif