






#ifndef VFD_CONTROL_H
#define VFD_CONTROL_H




#include"vfdcommands.h"



#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

// Will have to be changed later
const char* portname = "ttyUSB0";


char vfdbuffer_recieve[64];

int vfd_fd;

int openPort(const char* name);

bool configPort(int code, int speed);

int openPort();

void closePort();

char* readPort();

int writePort(const char* send);

int writePacket(packet p);

#endif