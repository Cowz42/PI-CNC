





#include<iostream>
#include"clidisplay.hpp"
#include"../globaldef/socketmanager.hpp"




int main(int argc, char** argv) {



    std::cout << "This is not going to work first try\n";

    net_socket.start(false);

    std::cout << net_socket.recieve() << "\n";

    net_socket.transmit("Hi, this is john client :)");

    std::cout << net_socket.recieve() << "\n";
    std::cout << net_socket.recieve() << "\n";

    return 0;
}