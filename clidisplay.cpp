







#include"clidisplay.h"
#include<iostream>
#include<curses.h>
#include"globalcommunication.h"
#include"programrun.h"
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<filesystem>



std::vector<std::string> files;

int cursorLine;
int cliMode = 0;

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
    keypad(stdscr, TRUE);
    noecho();



    printw("Starting up CNC\n");
    refresh();



    std::string path = "/home/cnc/Downloads/";
    
    int i = 0;
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        files.push_back(entry.path());
    }


    return 0;
}

void filePicker() {

    if (cursorLine > files.size() - 1) {
        cursorLine = 0;
    } else if (cursorLine < 0) {
        cursorLine = files.size() - 1;
    }

    move(0,0);
    
    for (int i = 0; i < files.size(); i++) {
        printw("%s  %s", i == cursorLine ? "*" : " ", files.at(i));
    }
    int ch;
    ch = getch();

    if (ch == KEY_UP) {
        cursorLine--;
    } else if (ch == KEY_DOWN) {
        cursorLine++;
    } else if (ch == KEY_ENTER) {
        FileLoadGlobal(files.at(cursorLine));
        cliMode = 1;
    }
}


void nonRunning() {

}

void running() {

}

void CLI::update() {
    if (cliMode== 0) {
        filePicker();
    } else if (cliMode == 1) {
        nonRunning();
    } else if (cliMode == 2) {
        running();
    } else {
        std::cerr << "CLI Mode error, returning to file select\n";
        cliMode = 0;
    }
}


void CLI::end() {
    endwin();
}


void updateCommandBuffer() {
    move(0,0);

}

void updateInfoBuffer() {

}


void FileLoadGlobal(std::string filename) {
    WorkingFileGlobal = filename;
}