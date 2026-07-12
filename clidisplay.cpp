







#include"clidisplay.h"
#include<iostream>
#include<curses.h>
#include"globalcommunication.h"
#include"programrun.h"




StepperControl* g;


int CLI::start() {
    g = CNC.getGantry();
    if (g == nullptr) {
        std::cerr << "No gantry detected\n";
        return -1;
    }

    if (initscr() == NULL) {
        std::cerr << "Unable to start ncurses\n";
        return -1;
    }
    printw("Starting up CNC\n");
    refresh();
}

void CLI::update() {
    
}


void CLI::end() {
    endwin();
}