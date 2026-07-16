







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

std::string WorkingFileGlobal = "";

std::vector<std::string> file;

std::vector<std::string> files;

std::vector<std::string> fileBuffer;

uint fileposition = 0;

#define ENTER_REAL 10

std::string path = "/home/cnc/Downloads/";


WINDOW* list;
WINDOW* info;


int cursorLine;

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

    list = newwin(LINES_A, COLS, 0, 0);
    info = newwin(5, COLS, LINES_A, 0);

    keypad(list, TRUE);
    noecho();

	wtimeout(list, 500);

    mvwprintw(list, 0, 0, "Starting up CNC\n");


    refresh();

    wgetch(list);

    
    int i = 0;
    for (const auto & entry : fs::directory_iterator(path)) {
        files.push_back(entry.path());
    }


    return 0;
}

void filePicker() {
    wtimeout(list, 10);

    if (cursorLine > files.size() - 1) {
        cursorLine = 0;
    } else if (cursorLine < 0) {
        cursorLine = files.size() - 1;
    }

    mvwprintw(list, 3, 0, "Files list at: %s, Cursor at: %d\n", path.data(), cursorLine);
    // buffer.append("Files list at /home/cnc/Downloads\n");
    int i = 0;
    for (; i < files.size() && i < LINES_A; i++) {
        // buffer.append(std::to_string(i));
        // buffer.append("  ");
        // buffer.append(files.at(i).substr(path.size()));
        // buffer.append("\n");
        wprintw(list, "%d  %s\n",i, files.at(i).substr(path.size()).data());
    }

    for (;i < LINES_A; i++) {
        // buffer.append("\n");
        wprintw(list, "\n");
    }


    int ch;
    ch = wgetch(list);

    if (ch == KEY_UP) {
        cursorLine--;
    } else if (ch == KEY_DOWN) {
        cursorLine++;
    } else if (ch == ENTER_REAL) {
        FileLoadGlobal(path + files.at(cursorLine));
        cliMode = 1;
	    std::cerr << "Loading file\n";
    }
}


void nonRunning() {
    std::cerr << "Hopefully Loaded the file, gotta figure that out too\n";
}

void running() {

}

void infoDisp() {
    wtimeout(info,0);
    box(info, 0, 0);
    wmove(info, 1, 1);
    wprintw(info, "CNC system information\n");
    wprintw(info, "X: %+8.3f,   Y: %+8.3f,   Z: %+8.3f\n", 5.3, 5.2, 5.1);
}

void CLI::update() {
	// buffer = "FILES\tFILE\tERROR\n\n";
    mvwprintw(list, 0, 0, "FILES\tFILE\tERROR\n");
	std::cerr << "IDK 1\n";
    if (cliMode== 0) {
        filePicker();
    } else if (cliMode == 1) {
        std::cerr << "edit mode enabled\n";
        nonRunning();
    } else if (cliMode == 2) {
        running();
    } else {
        std::cerr << "CLI Mode error, returning to file select\n";
        cliMode = 0;
    }
    // printw("%s\n", buffer.data());
	std::cerr << "IDK 2\n";
    infoDisp();
	refresh();
}


void CLI::end() {
    endwin();
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

