







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
#define MANUAL_OPTIONS_SIZE 11

std::string headers[HEADERS_LIST_SIZE] = {
    "FILES",
    "FILE",
    "CONTROL",
    "ERROR"
};

std::string maunualOptions[11] = {
    "X: ",                          // 0
    "Y: ",
    "Z: ",
    "A: ",
    "B: ",
    "C: ",
    "RPM:",
    "HOME",
    "COOLING",
    " ",
    "CMD: "                         // 10
};

std::string manualCMD;


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
bool stredit(std::string* str, int chin);

// returns true if an edit has taken place, false otherwise
bool stredit(std::string* str, int chin) {
    if (str == nullptr || cursorLine != 10) {
        return false;
    }
    if (chin > 31 && chin < 127) {
        std::string out = "";

        if (cursorCol != 0) {
            out.append((*str).substr(0, cursorCol));
        }

        out.push_back((char)chin);

        if (cursorCol != (*str).size()) {
            out.append((*str).substr(cursorCol));
        }

        (*str).clear();
        (*str).append(out);
        cursorCol++;
        return true;

    } else if (chin == KEY_BACKSPACE) {
        if (cursorCol == 0) {
            return false;
        } else if (cursorCol == 1) {
            (*str) = (*str).substr(1);
            cursorCol--;
            return true;
        } else if (cursorCol == (*str).size()) {
            (*str) = (*str).substr(0, (*str).size() - 1);
            cursorCol--;
            return true;
        }

        std::string a = (*str).substr(0, cursorCol - 1);
        std::string b = (*str).substr(cursorCol);

        (*str).clear();
        (*str).append(a);
        (*str).append(b);
        cursorCol--;
        return true;


    }
    return false;
}




void windowChangeCheck(int charnum) {
    if (charnum > 47 && charnum < 52) {
        setMode(charnum - 48);
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
    } else if (cliMode == 2) {
        if (cursorLine >= MANUAL_OPTIONS_SIZE) {
            cursorLine = 0;
        } else if (cursorLine < 0) {
            cursorLine = MANUAL_OPTIONS_SIZE - 1;
        }

        if (cursorLine == 10) {
            if (cursorCol < 0) {
                cursorCol = 0;
            } else if (cursorCol > manualCMD.size()) {
                cursorCol = manualCMD.size();
            }
        } else {
            cursorCol = 0;
        }
    }



    if (cursorLine < scrollLine) {
        scrollLine = cursorLine;
    } else if (cursorLine > scrollLine + (LINES_A - 1)) {
        std::cerr << "limit a\n";
        scrollLine = cursorLine - (LINES_A - 1);
    }


    if (scrollLine < 0) {
        scrollLine = 0;
    }

    if (cliMode == 0) {
        if (scrollLine + LINES_A > files.size()) {
            // scrollLine = files.size() - LINES_A;
        }
    } else if (cliMode == 1) {
        if (scrollLine + LINES_A > file.size()) {
            // scrollLine = file.size() - LINES_A;
        }
    } else if (cliMode == 2) {
        if (scrollLine + LINES_A > MANUAL_OPTIONS_SIZE) {
            scrollLine = MANUAL_OPTIONS_SIZE - LINES_A;
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

        if (file.size() == 0) {
            mvwprintw(list, 0, 0, "No File Loaded");
            mvwprintw(list, 1, 0, "Press any key to continue");
            wtimeout(list, -1);
            wgetch(list);
            wtimeout(list, 0);
            setMode(0);
            return;
        }

        mvwprintw(list, 0, 0, "File %s", WorkingFileGlobal.data());

        

        for (int i = 0; i + scrollLine < file.size() && i < LINES_A; i++) {
            mvwprintw(list, i + 1, 0, "%s %06d  %s", fileposition == i+scrollLine ? ">" : " ", i + scrollLine, file.at(i + scrollLine).data());
        }

        
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
    } else if (ch == KEY_LEFT) {
        cursorCol--;
    } else if (ch == KEY_RIGHT) {
        cursorCol++;
    }

    windowChangeCheck(ch);

    cursorCheck();
}

void manual() {
    if (cursorChange) {
        cursorChange = false;
        wclear(list);

        mvwprintw(list, 0, 0, "Manual Control Options");

        for (int i = 0; i < MANUAL_OPTIONS_SIZE; i++) {

            // placeholders for now, gotta add later
            float num = 2.85;
            bool enabled = true;

            mvwprintw(list, i + 1, 0, "%s   ", maunualOptions[i].data());
            if (i < 7) {
                wprintw(list, "%f", num);
            } else if (i == 8) {
                wprintw(list, "%s", enabled ? "ON" : "OFF");
            } else if (i == 10) {
                wprintw(list, "%s", manualCMD.data());
            } else if (i == 9) {
                wprintw(list, "L: %d, C: %d, S: %d", cursorLine, cursorCol, manualCMD.size());
            }
        }

    }

    wmove(list, cursorLine + 1, cursorLine == 10 ? cursorCol + 8 : maunualOptions[cursorLine].size() + 3);

    int ch;
    ch = wgetch(list);

    wrefresh(list);

    bool streditnumlock = true;

    if (ch != ERR) {
        streditnumlock = !stredit(&manualCMD, ch);
        cursorChange = true;
    }

    if (ch == KEY_UP) {
        cursorLine--;
    } else if (ch == KEY_DOWN) {
        cursorLine++;
    } else if (ch == KEY_LEFT) {
        cursorCol--;
    } else if (ch == KEY_RIGHT) {
        cursorCol++;
    }

    if (streditnumlock) {
        windowChangeCheck(ch);
    }

    cursorCheck();
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
    file.shrink_to_fit();
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
