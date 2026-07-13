



#include"gcode.h"
#include"commands.h"


#ifndef GCODE_INTERFACE_H
#define GCODE_INTERFACE_H

// interfaces different command storage methods, converts a GCodeInstruction to a Cmd
Cmd convertGCode(GCodeInstruction a) {
    Cmd out;
    out.x = a.x;
    out.y = a.y;
    out.z = a.z;
    out.i = a.i;
    out.j = a.j;
    out.f = a.f;
    out.s = a.s;

    out.USED = 0x00;

    if (a._x) {
        out.USED |= X_BM;
    }
    if (a._y) {
        out.USED |= Y_BM;
    }
    if (a._z) {
        out.USED |= Z_BM;
    }
    if (a._i) {
        out.USED |= I_BM;
    }
    if (a._j) {
        out.USED |= J_BM;
    }
    if (a._f) {
        out.USED |= F_BM;
    }
    if (a._s) {
        out.USED |= S_BM;
    }
    out.num = a.command_number;
    out.letter = a.command_char;


    return out;
}




#endif
