// Gets rid of errors while on my laptop, and should still compile correctly on the pi
#ifndef __x86_64__
#include<wiringPi.h>
#else

#ifndef _RASPI_IO_VIRT_H
#define _RASPI_IO_VIRT_H

#ifndef OUTPUT
#define OUTPUT 0
#endif

#ifndef INPUT
#define INPUT 1
#endif

#ifndef LOW
#define LOW 0
#endif

#ifndef HIGH
#define HIGH 1
#endif

// Macros for the basic pin functions when compiling for x86_64

#include<string>
#include"../globaldef/globalcommunication.hpp"

#define pinMode(p, d) sys_log("pinMode " + std::to_string(p) + ", " + std::to_string(d) + "Not defined when compilied on x86_64\n");
#define digitalWrite(p, d) sys_log("digitalWrite " + std::to_string(p) + ", " + std::to_string(d) + "Not defined when compilied on x86_64\n");


// void digitalWrite(int p, int d) {}



#endif

#endif
