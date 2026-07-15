







#include"clidisplay.h"
#include<string>
#include<iostream>
#include<curses.h>
#include"globalcommunication.h"
#include"programrun.h"
#include<vector>
#include<fstream>
#include<iostream>
#include<filesystem>
#include"file.h"

namespace fs = std::filesystem;

std::string WorkingFileGlobal;

std::vector<std::string> file;

std::vector<std::string> files;

std::vector<std::string> fileBuffer;



unsigned int cursorLine;

// 0 = file picker
// 1 = non run
// 2 = running
// 3 = error log
int cliMode = 0;

StepperControl* gantryCLI;


int CLI::start() {
    cliMode = 0;
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
    for (const auto & entry : fs::directory_iterator(path)) {
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
    printw("Files list at /home/cnc/Downloads\n");
    printw("Files detected %d\n", files.size());


    for (int i = 0; i < files.size(); i++) {
        printw("%s  %s\n", i == cursorLine ? "*" : " ", files.at(i));
    }
    printw("%d\n",cursorLine);
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
    refresh();
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
    if (filename.compare("") != 0) {
        WorkingFileGlobal = filename;
    }
    file.clear();
    std::ifstream f(WorkingFileGlobal);
    std::string line = "";
    while(!f.eof()) {
        getline(f, line);
        file.push_back(line);
    }
    f.close();
    cursorLine = 0;
}

void loadFileBuffer() {
    if (cliMode == 1 || cliMode == 2) {
        fileBuffer.clear();
        for (uint i = cursorLine; i < cursorLine + LINES_A; i++) {
            fileBuffer.push_back(file.at(i));
        }
    } else if (cliMode == 3) {
        for (uint i = cursorLine; i < cursorLine + (errArr.size() > LINES_A ? LINES_A : errArr.size()); i++) {

        }
    }
}