





#include<iostream>
#include<string>
#include"clidisplay.hpp"
#include"../globaldef/socketmanager.hpp"
#include"../globaldef/globalcommunication.hpp"




CLI cli;

std::string ip_input;



int main(int argc, char** argv) {

    
    ip_input = "127.0.0.1";


    prgm_log("CLI Starting\n");



    cli.start();


    net_socket.start(ip_input);
    

    while(true) {
        cli.update();
        if (prgm_exit) {
            prgm_log("Exiting\n");
            sys_log("Client Exiting\n");
            break;
        }
    }

    net_socket.end();

    cli.end();


    // net_socket.start(false);

    return 0;
}