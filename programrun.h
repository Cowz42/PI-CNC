



#ifndef PROGRAM_RUN_H
#define PROGRAM_RUN_H


#include"positioncalc.h"

class CNC {
public:
    static void start();
    static void startProgram(std::string name);
    static void run();
    // allows external functions to read information on the gantry
    static StepperControl* getGantry();
};


extern CNC cnc;





#endif