


#include<iostream>
// #include"displaycontroller.h"
#include"clidisplay.h"

CLI cli;

int main(int argc, char** argv) {

    std::cerr << "Starting cli\n";

    if (cli.start() == -1) {
        exit(EXIT_FAILURE);
    }
	bool a = false;
    std::cerr << "Started Successfully\n";

    while(1) {
        cli.update();
        if (a == false) {
            std::cerr << "Update Ran once\n";
            a = true;
        }
    }

    std::cout << "I still need to write the main method for this project\n";


    return 0;
}
