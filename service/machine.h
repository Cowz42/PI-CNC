// File Containing information about the specifications of the device
// Units are in mm or miliseconds



#ifndef MACHINE_SPEC_H
#define MACHINE_SPEC_H



// Gantry size
#define MAX_X 100
#define MIN_X 0
#define MAX_Y 100
#define MIN_Y 0
#define MAX_Z 100
#define MIN_Z 0

// Speed, it is all directional speed
#define MAX_SPEED_GANTRY 55

#ifndef MAX_SPEED_X
#define MAX_SPEED_X MAX_SPEED_GANTRY
#endif
#ifndef MAX_SPEED_Y
#define MAX_SPEED_Y MAX_SPEED_GANTRY
#endif
#ifndef MAX_SPEED_Z
#define MAX_SPEED_Z MAX_SPEED_GANTRY
#endif


// Stepper Pins
// PLACE HOLDERS FOR NOW
// X-axis Stepper
#define X_1 1
#define X_2 2
#define X_3 3
#define X_4 4

// Y-axis Stepper
#define Y_1 5
#define Y_2 6
#define Y_3 7
#define Y_4 8

// Z-axis Stepper
#define Z_1 9
#define Z_2 10
#define Z_3 11
#define Z_4 12





#endif