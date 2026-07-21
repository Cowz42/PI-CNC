/*
    Header file for communication commands and the like between componenets


*/

#ifndef COMMANDS_H
#define COMMANDS_H


#define X_BM 0x80
#define Y_BM 0x40
#define Z_BM 0x20
#define I_BM 0x10
#define J_BM 0x08
#define S_BM 0x04
#define F_BM 0x02






struct Cmd
{
    char letter;
    int num;
    float x;
    float y;
    float z;
    float i;
    float j;
    float s;
    float f;
    unsigned char USED;

};




#endif