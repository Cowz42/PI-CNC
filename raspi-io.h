// Gets rid of errors while on my laptop, and should still compile correctly on the pi
#ifndef __x86_64__
#include<wiringPi.h>
#include<pcf8574.h>
#else
#define OUTPUT 0
#define LOW 0
#define HIGH 1
void pinMode(int p, char d) {}
void digitalWrite(int p, int d) {}
#endif