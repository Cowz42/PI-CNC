







#ifndef GLOBAL_COM_H
#define GLOBAL_COM_H

#include<iostream>
#include<string>


void pushError(std::string err);
void pushMessage(std::string msg);

std::string getMessage();
std::string getError();

bool checkError();
bool checkMessage();




#endif