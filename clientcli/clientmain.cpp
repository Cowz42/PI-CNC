





#include<iostream>
#include"clidisplay.hpp"
#include"../globaldef/socketmanager.hpp"



CLI cli;


int main(int argc, char** argv) {



    std::cout << "This is not going to work first try\n";

    cli.start();

    while(true) {
        cli.update();
    }

    cli.end();


    // net_socket.start(false);

    return 0;
}