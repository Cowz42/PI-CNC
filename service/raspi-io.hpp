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

void pinMode(int p, char d) {}
void digitalWrite(int p, int d) {}

#endif

#endif
