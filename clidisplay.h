




#ifndef COMMAND_LINE_INTERFACE_DISPLAY_H
#define COMMAND_LINE_INTERFACE_DISPLAY_H

#include<string>



class CLI {
    // starts the cli display, returns -1 if something fails
    int start();
    void end();
    void update();
};

std::string WorkingFileGlobal;

void FileLoadGlobal(std::string filename);





#endif