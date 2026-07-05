



#ifndef STEPPER_H
#define STEPPER_H


#ifdef _WIN32
#include<F:\Network Share Colin\Code\Libraries\WiringPi\WiringPi\wiringPi.h>
#endif

#ifdef __linux__
#include<wiringPi.h>
#endif






class Stepper {
    private:
    // pin Numbers for the stepper
    int a, b, c, d;
    // float so we can move decimal distance
    float position;
    // Decimal points chopped off for the actual stepper steps
    int pos;
    // multiplier to put on the stepper motor, allows better control
    float gearing;
    // Steps the Stepper takes to make a full revolution
    int steps;

    // Recalcs the pins based off of the current position
    void pin_update();
    public:
    // Contstructor, pin1 thru pin4 are the pins that the stepper will use
    // gear_ratio is the ratio between the output : motor revolutions
    // steps is the amoun of steps to make a full rotation
    // invert swaps the direction the motor will travel
    Stepper(int pin1, int pin2, int pin3, int pin4, float gear_ratio, int steps, bool invert = false);
    void setPosition(float x);
    bool update();
    void start();

};














#endif