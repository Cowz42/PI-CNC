

#ifndef FILE_MANAGE_CNC_H
#define FILE_MANAGE_CNC_H


#include<string>
#include<vector>


extern std::string WorkingFileGlobal;
extern std::vector<std::string> file;
extern uint fileposition;

int FileLoadGlobal(std::string filename);

#endif