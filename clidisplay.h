




#ifndef COMMAND_LINE_INTERFACE_DISPLAY_H
#define COMMAND_LINE_INTERFACE_DISPLAY_H

#include<string>
#include<vector>



class CLI {
    // starts the cli display, returns -1 if something fails
    public:
    int start();
    void end();
    void update();
};

#define LINES_A 25

extern uint fileposition;

extern std::string WorkingFileGlobal;

extern std::vector<std::string> errArr;
extern std::vector<std::string> msgArr;


#endif