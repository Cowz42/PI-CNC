





#ifndef VFD_MOTOR_H
#define VFD_MOTOR_H

#include"vfdcommands.h"

float modFloatAngle(float n) {
    while (n > 360) {
        n -= 360;
    }
    return n;
}

class VFDMotor {
    public:
    // Set speed in RPM
    float speedSet;
    // Real speed in RPM
    float speed;
    // Current angle relative to start
    float currentPos;
    // Acceleration in RPM/s
    float accelMax;
    // Maximum Speed in RPM
    float speedMax;
    // Maximum Current in milliamps
    float currMax;
    // the three poles of the motor
    float a, b, c;
    // current sensed values for the motor
    float currA, currB, currC;

    
    
    VFDMotor() {
        speedSet = 0;
        speed = 0;
        currentPos = 0;
        accelMax = 1;
        speedMax = 1;
        currMax = 100;
    }

    void setMaxSpeed(float s) {
        speedMax = s;
    }
    void setMaxAccel(float a) {
        accelMax = a;
    }
    void setSpeed(float s) {
        if (s > speedMax) {
            // Throw an error
            Serial.println(packetStrBuilder((packet){0, 9}));
            return;
        }
        speedSet = s;
    }
    
    float getPos() {
        return currentPos;
    }

    void setPos(float p) {
        currentPos = modFloatAngle(p);
    }

    void stop() {
        speedSet = 0;
    }

    void update() {
        a = sin(currentPos);
        b = sin(currentPos + 120);
        c = sin(currentPos + 240);
    }
    void run() {
        if (currA > currMax || currB > currMax || currC > currMax) {
            // Send an overcurrent error
            Serial.println(packetStrBuilder((packet){0, 1}));
            this->stop();
        }
        if (currA + 15 > currMax || currB + 15 > currMax || currC > currMax) {

        }
    }

    void start() {
        
    }
};









#endif