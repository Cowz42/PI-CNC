


#include<vector>
#include<string>
#include"file.h"
#include<iostream>
#include<fstream>





uint fileposition = 0;

std::string WorkingFileGlobal = "";

std::vector<std::string> file;


int FileLoadGlobal(std::string filename) {
    if (filename.compare("") != 0) {
        WorkingFileGlobal = filename;
    }
    file.clear();
    std::cerr << "Loading file \"" << WorkingFileGlobal << "\" to the program\n";
    std::ifstream f(WorkingFileGlobal);
    std::string line = "";
    if (!f.is_open()) {
        std::cerr << "File Open Failure\n";
        return -1;
    }
    while(!f.eof()) {
        getline(f, line);
        file.push_back(line);
    }
    f.close();
    file.shrink_to_fit();
    return 0;
}