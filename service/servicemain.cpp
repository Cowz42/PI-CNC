


#define SERVICE_SOCKET




#include"programrun.hpp"
#include"../globaldef/socketmanager.hpp"
#include<unistd.h>
#include<string>
#include<iostream>


int main(int argc, char** argv) {

    cnc.start();
    while(!s.start(true)) {
        usleep(15000);
    }

    s.transmit("Hello, this is joseph server :)");

    std::string hello = s.recieve();

    std::cout << hello << "\n";

    s.transmit("Hello client, sending back :) ");
    s.transmit(hello);
    

    return 0;
}
