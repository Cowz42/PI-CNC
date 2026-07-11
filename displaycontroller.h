




#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include<iostream>

#define GLFW_INCLUDE_NONE
#include "./lib/glfw-3.4/include/GLFW/glfw3.h"



GLFWwindow* window;



bool keys_input[256];



// Starts the display systems
// false return means it failed, and may need to be started again or checked in some other ways
bool start();


// Stops the display, call on program exit
void close();

// Error Handler for GLFW
void error_callback(int error, const char* description);

// called when the user attempts to close the window
void close_callback(GLFWwindow* w);


// Used to add any function to a specific key, called whenever it is pressed
void setKeyCallback(void (*fn)(int key, int action, int mods), unsigned int index);


#endif
