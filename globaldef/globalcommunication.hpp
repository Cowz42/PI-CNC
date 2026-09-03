







#ifndef GLOBAL_COM_H
#define GLOBAL_COM_H

#include<iostream>
#include<string>
#include<vector>


// Send error to local program
void prgm_error(std::string msg);

// Log to local program
void prgm_log(std::string msg);

// Send system error to other program(client/server)
void sys_error(std::string msg);

// Send system log to other program(client/server)
void sys_log(std::string msg);

// Set the file used for the program log
void mountLogFile(std::string name);

// Set the file used for the program error
void mountErrorFile(std::string name);

// Deattach the files that are used for logging and errors
void umountFiles();

#endif