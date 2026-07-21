



#include"gcode.h"
#include"commands.h"


#ifndef GCODE_INTERFACE_H
#define GCODE_INTERFACE_H

// interfaces different command storage methods, converts a GCodeInstruction to a Cmd
Cmd convertGCode(GCodeInstruction a);




#endif
