







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
#include<algorithm>

namespace fs = std::filesystem;

std::string WorkingFileGlobal = "";

std::vector<std::string> file;

std::vector<std::string> files;

std::vector<std::string> fileBuffer;

uint fileposition = 0;

#define ENTER_REAL 10

std::string path = "/home/cnc/Downloads/";

#define HEADERS_LIST_SIZE 4

std::string headers[HEADERS_LIST_SIZE] = {
    "FILES",
    "FILE",
    "CONTROL",
    "ERROR"
};


WINDOW* list;
WINDOW* info;
WINDOW* header;

bool cursorChange;
bool infoChange;


int cursorLine;
int cursorCol;
int scrollLine;

// 0 = file picker
// 1 = preview
// 2 = running
// 3 = error log
int cliMode = 0;

StepperControl* gantryCLI;

void setMode(int mode);
void fileView();
void manual();
void infoDisp();
void headerUpdate();
void infoStart();
void filePicker();
void cursorCheck();
void windowChangeCheck(int charnum);




void windowChangeCheck(int charnum) {
    if (charnum > 47 && charnum < 52) {
        setMode(charnum - 48);
        std::cerr << "Switching mode too: " << charnum - 48 << "\n";
        return;
    }
}


void cursorCheck() {
    if (cliMode == 0) {
        if (cursorLine >= files.size()) {
            cursorLine = 0;
        } else if (cursorLine < 0) {
            cursorLine = files.size() - 1;
        }
    } else if (cliMode == 1) {
        if (cursorLine >= file.size()) {
            cursorLine = 0;
        } else if (cursorLine < 0) {
            cursorLine = file.size() - 1;
        }
        if (cursorCol < 0) {
            cursorCol = 0;
        } else if (cursorCol > file.at(cursorLine).size()) {
            cursorCol = file.at(cursorLine).size();
        }
    }



    if (cursorLine < scrollLine) {
        scrollLine = cursorLine;
    } else if (cursorLine >= scrollLine + (LINES_A - 1)) {
        scrollLine = cursorLine - (LINES_A - 2);
    }
    if (scrollLine < 0) {
        scrollLine = 0;
    }

    if (cliMode == 0) {
        if (scrollLine + LINES_A > files.size()) {
            scrollLine = files.size() - LINES_A;
        }
    } else if (cliMode == 1) {
        if (scrollLine + LINES_A > file.size()) {
            scrollLine = file.size() - LINES_A;
        }
    }
}


void setMode(int mode) {
    cliMode = mode;

    headerUpdate();
    infoStart();
    infoDisp();
    scrollLine = 0;
    cursorLine = 0;
    infoChange = true;
    cursorChange = true;

}

void fileView() {
	if (cursorChange) {
        cursorChange = false;
        wtimeout(list, 0);

        wclear(list);



        mvwprintw(list, 0, 0, "File %s", WorkingFileGlobal.data());

        for (int i = 0; i + scrollLine < files.size() && i < LINES_A; i++) {
            mvwprintw(list, i + 1, 0, "%s %06d  %s", fileposition == i+scrollLine ? ">" : " ", i + scrollLine, file.at(i + scrollLine).data());
        }

        wmove(list, cursorLine + 1 - scrollLine, cursorCol + 10);

        int ch;
        ch = wgetch(list);

        wrefresh(list);

        if (ch != ERR) {
            cursorChange = true;
        }

        if (ch == KEY_UP) {
            cursorLine--;
        } else if (ch == KEY_DOWN) {
            cursorLine++;
        }

        windowChangeCheck(ch);

        cursorCheck();
	}
}

void manual() {

}

void infoDisp() {
    if (infoChange) {
        infoChange = false;
        mvwprintw(info, 1, 1, "X: %+8.3f,   Y: %+8.3f,   Z: %+8.3f", 5.3, 5.2, 5.1);
        wrefresh(info);
    }
}

void headerUpdate() {
    wclear(header);
    wmove(header, 0, 0);
    for (int i = 0; i < HEADERS_LIST_SIZE; i ++) {
        if (cliMode == i) {
            wattron(header, A_BOLD);
        }
        wprintw(header, "%15s", headers[i].data());
        if (cliMode == i) {
            wattroff(header, A_BOLD);
        }
    }

    // mvwprintw(header, 0, 0, "%15s %15s %15s %15s", "FILES", "FILE", "CONTROL", "ERROR");
    
    wrefresh(header);
}

void infoStart() {
    wclear(info);
    box(info, 0, 0);
    mvwprintw(info, 0, 1, "CNC system information");
}




void FileLoadGlobal(std::string filename) {
    if (filename.compare("") != 0) {
        WorkingFileGlobal = filename;
    }
    file.clear();
    std::cerr << "Loading file \"" << WorkingFileGlobal << "\" to the program\n";
    std::ifstream f(WorkingFileGlobal);
    std::string line = "";
    if (!f.is_open()) {
        std::cerr << "File Open Failure\n";
        return;
    }
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

    if (cursorChange) {
        cursorChange = false;
        wclear(list);
        wtimeout(list, 50);
        
    

        mvwprintw(list, 0, 0, "Files list at: %s C: %d S: %d Size: %d", path.data(), cursorLine, scrollLine, files.size());
        // buffer.append("Files list at /home/cnc/Downloads\n");
        
        for (int i = 0; i + scrollLine < files.size() && i < LINES_A; i++) {
            mvwprintw(list, i + 1, 0, "%d  %s",i + scrollLine, files.at(i + scrollLine).substr(path.size()).data());
        }

    }

	wmove(list, cursorLine + 1 - scrollLine, 0);

    int ch;
    ch = wgetch(list);

    wrefresh(list);

    if (ch != ERR) {
        cursorChange = true;
    }

    if (ch == KEY_UP) {
        cursorLine--;
    } else if (ch == KEY_DOWN) {
        cursorLine++;
    } else if (ch == ENTER_REAL) {
        wclear(list);
        mvwprintw(list, 0, 0, "Loading File %s", files.at(cursorLine).data());
        FileLoadGlobal(files.at(cursorLine));
        setMode(1);
    }
	windowChangeCheck(ch);

    cursorCheck();
}


int CLI::start() {
    cursorChange = true;
    infoChange = true;
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
    list = newwin(LINES_A + 1, COLS, 3, 0);
    info = newwin(5, COLS, LINES_A + 8, 0);

    keypad(list, TRUE);
    noecho();
    cbreak();

	wtimeout(list, -2);
    wtimeout(info,0);
    wtimeout(header,0);

    mvwprintw(list, 0, 0, "Starting up CNC\n");


    refresh();

    wgetch(list);

    
    int i = 0;
    for (const auto & entry : fs::directory_iterator(path)) {
        files.push_back(entry.path());
    }
    std::sort(files.begin(), files.end(), [](std::string a, std::string b) {return a.compare(b) < 0;});
    


    headerUpdate();
    infoStart();
	infoDisp();
    return 0;
}


void CLI::update() {
    if (cliMode== 0) {
        filePicker();
    } else if (cliMode == 1) {
        fileView();
    } else if (cliMode == 2) {
        manual();
    } else if (cliMode == 3) {

    } else {
        std::cerr << "CLI Mode error, returning to file select\n";
        setMode(0);
    }
    infoDisp();
	// refresh();
}


void CLI::end() {
    endwin();
}
