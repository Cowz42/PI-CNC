







#include"clidisplay.h"
#include<iostream>
#include<curses.h>
#include"globalcommunication.h"
#include"programrun.h"




StepperControl* gantry;


int CLI::start() {
    gantry = cnc.getGantry();
    if (gantry == nullptr) {
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