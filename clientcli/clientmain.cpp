





#include<iostream>
#include"clidisplay.h"
#include"../service/socketmanager.h"




int main(int argc, char** argv) {



    std::cout << "This is not going to work first try\n";

    s.start();

    std::cout << s.recieve() << "\n";

    s.transmit("Hello there :)");


    std::cout << s.recieve() << "\n";
    std::cout << s.recieve() << "\n";

    return 0;
}