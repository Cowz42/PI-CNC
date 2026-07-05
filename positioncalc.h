/*
assumes units of mm and microseconds respectivly

angles are in degrees starting with zero being positive x rotating around the z axis counter-clockwise


*/


#ifndef POSITION_CALC_H
#define POSITION_CALC_H



#include"machine.h"
#include<math.h>
#include"commands.h"

class StepperControl
{
    private:
    // Current coordinate mode
    bool absolute;

    // inches or metric
    bool imperial;

    // Offsets, used to set home value
    float x_offset, y_offset, z_offset;

    // Feed Speed and Spindle speed values
    float f, s;

    // starting position for every command
    float x_start, y_start, z_start;

    // current position
    float x_pos, y_pos, z_pos;

    // multipliers used for math
    float x_mult, y_mult, z_mult;

    // float scaling;

    // time since instruction start, in microseconds
    float time;

    // maximum time value for the current instruction to finish
    float timeMax;

    // flag for it being a linear instruction
    bool linear;

    // flag for it being a circular interpolation instruction
    bool circular;

    // flag that further specifies clockwise and counter-clockwise
    bool clockwise;

    // radius for circle math
    float r;
    
    // starting angle for circle math
    float theta;

    // ending angle for circle math
    float thetaEnd;

    // current working instruction
    Cmd ins;

    public:

    // Sets the next instruction
    void setInstruction(Cmd m);
    
    // calculates next x, y, and z values for the given delta time
    bool step(float dt);


    // calculates next x, y, and z values for the given delta time
    bool step(int dt);

    // returns the current coordinate
    float getX();


    // returns the current coordinate
    float getY();


    // returns the current coordinate
    float getZ();

    // sets the current position as the new home
    void home();

    // sets the passed position as the new home
    void setHomePosition(float x, float y, float z);


    // set the working value to a specific point
    void setX(float x);

    // set the working value to a specific point
    void setY(float y);

    // set the working value to a specific point
    void setZ(float z);

    void setF(float f);

    void setAbsoluteCoordinate();

    void setRelativeCoordinate();

    void setImperial();

    void setMetric();
};











#endif