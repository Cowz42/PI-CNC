


#define SERVICE_SOCKET




#include"programrun.hpp"
#include"../globaldef/socketmanager.hpp"
#include<unistd.h>
#include<string>
#include<iostream>


int main(int argc, char** argv) {

    cnc.start();
    while(!net_socket.start(true)) {
        usleep(15000);
    }

    net_socket.transmit("Hello, this is joseph server :)");

    std::string hello = net_socket.recieve();

    std::cout << hello << "\n";

    net_socket.transmit("Hello client, sending back :) ");
    net_socket.transmit(hello);
    

    return 0;
}
