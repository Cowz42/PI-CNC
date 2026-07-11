



#ifndef PROGRAM_RUN_H
#define PROGRAM_RUN_H



#include<iostream>
#include<string>
#include"positioncalc.h"
#include"stepper.h"
#include"gcodeparse.h"
#include"gcodeinterface.h"
#include"gcode.h"
#include"machine.h"
#include"commands.h"
#ifdef _WIN32
#include"time.h"
#else
#include<sys/time.h>
#endif

class CNC {
    static void start();
    static void startProgram(std::string name);
    static void run();
};








#endif