







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
WINDOW* header;


int cursorLine;

// 0 = file picker
// 1 = non run
// 2 = running
// 3 = error log
int cliMode = 0;

StepperControl* gantryCLI;




void nonRunning() {
    std::cerr << "Hopefully Loaded the file, gotta figure that out too\n";
}

void running() {

}

void infoDisp() {
    mvwprintw(info, 1, 1, "X: %+8.3f,   Y: %+8.3f,   Z: %+8.3f\n", 5.3, 5.2, 5.1);
    wrefresh(info);
}

void headerUpdate() {
    wclear(header);
    mvwprintw(header, 0, 0, "FILES\tFILE\tERROR\n");
    wrefresh(header);
}

void infoStart() {
    wclear(info);
    box(info, 0, 0);
    mvwprintw(info, 0, 1, "CNC system information\n");

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



void filePicker() {
    wtimeout(list, 1000);
    wclear(list);

    if (cursorLine > files.size() - 1) {
        cursorLine = 0;
    } else if (cursorLine < 0) {
        cursorLine = files.size() - 1;
    }

    mvwprintw(list, 0, 0, "Files list at: %s, Cursor at: %d\n", path.data(), cursorLine);
    // buffer.append("Files list at /home/cnc/Downloads\n");
    int i = 0;
    for (; i < files.size() && i < LINES_A; i++) {
        wprintw(list, "%d  %s\n",i, files.at(i).substr(path.size()).data());
    }

    for (;i < LINES_A; i++) {
        wprintw(list, "\n");
    }


    int ch;
    ch = wgetch(list);

    wmove(list, cursorLine, 0);

    wrefresh(list);
    
    wmove(list, cursorLine, 0);

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

    header = newwin(3, COLS, 0, 0);
    list = newwin(LINES_A, COLS, 3, 0);
    info = newwin(5, COLS, LINES_A + 3, 0);

    keypad(list, TRUE);
    noecho();

	wtimeout(list, 500);
    wtimeout(info,0);
    wtimeout(header,0);

    mvwprintw(list, 0, 0, "Starting up CNC\n");


    refresh();

    wgetch(list);

    
    int i = 0;
    for (const auto & entry : fs::directory_iterator(path)) {
        files.push_back(entry.path());
    }


    headerUpdate();
    infoStart();

    return 0;
}


void CLI::update() {
    infoDisp();
	
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
	
	// refresh();
}


void CLI::end() {
    endwin();
}