
#include"stepper.h"


Stepper::Stepper(int pin1, int pin2, int pin3, int pin4, float gear_ratio, int steps, bool invert) {
    a = pin1;
    b = pin2;
    c = pin3;
    d = pin4;
    this->steps = steps;
    gearing = gear_ratio * (invert?-1:1);
}

void Stepper::start() {
    pinMode(a, OUTPUT);
    pinMode(b, OUTPUT);
    pinMode(c, OUTPUT);
    pinMode(d, OUTPUT);

    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);

    position = 0;
    pos = 0;
}



void Stepper::setPosition(float d) {
    position = d * gearing;
}


bool Stepper::update() {
    if ((int)position == pos) {
        return false;
    }

    if (position > pos) {
        pos++;
        pin_update();
    } else {
        pos--;
        pin_update();
    }
    return true;
}


void Stepper::pin_update() {
    if (pos % 4 == 0 || (pos + 1)  % 4 == 0) {
        digitalWrite(a, HIGH);
        digitalWrite(c, LOW);
    } else {
        digitalWrite(a, LOW);
        digitalWrite(c, HIGH);
    }

    if ((pos + 1) % 4 == 0 || (pos + 2) % 4 == 0) {
        digitalWrite(b, HIGH);
        digitalWrite(d, LOW);
    } else {
        digitalWrite(b, LOW);
        digitalWrite(d, HIGH);
    }

}