



#include"positioncalc.h"


#define PI 3.1415926535897932
#define DEG_RAD (PI / 180)
#define RAD_DEG (180 / PI)


float atanC(float x, float y) {
    if (x == 0) {
        if (y < 0) {
            return 270;
        }
        return 90;
    }
    float a = atan2(x, y) * RAD_DEG;
    return (a < 0) ? a + 360 : a;
}

void StepperControl::setInstruction(Cmd m) {
    ins = m;


    if (imperial) {
        ins.x *= 25.4;
        ins.y *= 25.4;
        ins.z *= 25.4;
        ins.i *= 25.4;
        ins.j *= 25.4; 
    }

    if (!absolute) {
        ins.x += x_pos;
        ins.y += y_pos;
        ins.z += z_pos;
        ins.i += x_pos;
        ins.j += y_pos;
    }


    // Ensures if a command doesn't contain all parts, it will copy over the previous ones
    if (!(ins.USED & X_BM)) {
        ins.x = x_pos;
    }
    if (!(ins.USED & Y_BM)) {
        ins.y = y_pos;
    }
    if (!(ins.USED & Z_BM)) {
        ins.z = z_pos;
    }
    if (!(ins.USED & S_BM)) {
        ins.s = s;
    }
    if (!(ins.USED & F_BM)) {
        ins.f = f;
    }

    if (ins.f >= MAX_SPEED_GANTRY || ins.num == 0) {
        ins.f = MAX_SPEED_GANTRY;
    }
    
    if (ins.num == 0 || ins.num == 1) {
        // G00 fast move, and G01 Linear interpolation
        linear = true;
        circular = false;
        clockwise = false;
    } else if (ins.num == 2) {
        // G02, circular interpolation clockwise
        linear = false;
        circular = true;
        clockwise = true;
    } else if (ins.num == 3) {
        // G03, circular interpolation counter-clockwise
        linear = false;
        circular = true;
        clockwise = false;
    } else if (ins.num == 4) {
        // G04, dwell
        linear = false;
        circular = false;
        clockwise = false;
    }
    
    x_start = x_pos;
    y_start = y_pos;
    z_start = z_pos;


    // Calculates the movements for G00 and G01

    if (linear) {

        float x_dist = ins.x - x_start;
        float y_dist = ins.y - y_start;
        float z_dist = ins.z - z_start;

        float dist = sqrt((x_dist * x_dist + y_dist * y_dist + z_dist * z_dist));

        time = 0;
        timeMax = (dist / ins.f) * 1000000;

        

        x_mult = x_dist / timeMax;
        y_mult = y_dist / timeMax;
        z_mult = z_dist / timeMax;
        return;
    } else if (circular) {
        r = sqrt((x_start - ins.i) * (x_start - ins.i) + (y_start - ins.j) * (y_start - ins.j));

        theta = atanC(x_start - ins.i, y_start - ins.j);
        thetaEnd = atanC(ins.x - ins.i, ins.y - ins.j);



        float dist = (abs(thetaEnd - theta) * 2 * PI * r) / 360;
        
        timeMax = (dist / ins.f) * 1000000;

        if (clockwise) {
            dist = -dist;
        }

        x_mult = dist / timeMax;
    } else {
        // will just 
        timeMax = 1000 * ins.f;
    }
}

bool StepperControl::step(float dt) {
    time += dt;
    if (time >= timeMax) {
        x_pos = ins.x;
        y_pos = ins.y;
        z_pos = ins.z;
        return false;
    }

    if (linear) {
        x_pos = time * x_mult + x_start;
        y_pos = time * y_mult + y_start;
        z_pos = time * z_mult + z_start;
    } else if (linear) {
        float a = time * x_mult + theta;
        x_pos = cos(DEG_RAD * (a)) + ins.i;
        y_pos = sin(DEG_RAD * (a)) + ins.j;
    }



    return true;
}

bool StepperControl::step(int dt) {
    return step(float(dt));
}

float StepperControl::getX() {
    return x_pos + x_offset;
}

float StepperControl::getY() {
    return y_pos + y_offset;
}

float StepperControl::getZ() {
    return z_pos + z_offset;
}

void StepperControl::setX(float x) {
    x_pos = x;
}

void StepperControl::setY(float y) {
    y_pos = y;
}

void StepperControl::setZ(float z) {
    z_pos = z;
}

void StepperControl::setF(float f) {
    this->f = f;
}

void StepperControl::home() {
    x_offset = x_pos;
    y_offset = y_pos;
    z_offset = z_pos;
}

void StepperControl::setHomePosition(float x, float y, float z) {
    x_offset = x;
    y_offset = y;
    z_offset = z;
}

void StepperControl::setAbsoluteCoordinate() {
    absolute = true;
}

void StepperControl::setRelativeCoordinate() {
    absolute = false;
}

void StepperControl::setImperial() {
    imperial = true;
}

void StepperControl::setMetric() {
    imperial = false;
}