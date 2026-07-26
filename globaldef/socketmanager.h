

#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H


#include<string>

class Socket {
    public:
    static bool starts();
    static bool startc();
    static void ends();
    static void endc();
    static void transmits(std::string msg);
    static void transmits(const char*);
    static void transmitc(std::string msg);
    static void transmitc(const char*);
    static std::string recieves();
    static std::string recievec();
};

extern Socket s;

#endif