







#include"clidisplay.h"
#include<iostream>
#include<curses.h>
#include"globalcommunication.h"
#include"programrun.h"




StepperControl* gantryCLI;


int CLI::start() {
    gantryCLI = cnc.getGantry();
    if (gantryCLI == nullptr) {
        std::cerr << "No gantry detected\n";
        return -1;
    }

    if (initscr() == NULL) {
        std::cerr << "Unable to start ncurses\n";
        return -1;
    }
    printw("Starting up CNC\n");
    refresh();

    return 0;
}

void CLI::update() {

}


void CLI::end() {
    endwin();
}
