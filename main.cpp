


#include<iostream>
// #include"displaycontroller.h"
#include"clidisplay.h"

CLI cli;

int main(int argc, char** argv) {

    cli.start();

    while(1) {
        cli.update();
    }

    std::cout << "I still need to write the main method for this project\n";


    return 0;
}