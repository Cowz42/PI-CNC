



#ifndef IOCONTROLLER_H
#define IOCONTROLLER_H

// To trick windows a little bit so I don't get errors

#ifdef _WIN32
#include<F:\Network Share Colin\Code\Libraries\WiringPi\WiringPi\wiringPi.h>
#define pcf8574Setup() 
#endif



#include"raspi-io.h"



#include"buttoninfo.h"

// Virtual ports by the i2c bus
#define VIRTUAL_PORTA 0x38
#define VIRTUAL_PORTB 0x39
#define VIRTUAL_PORTC 0x3A

#define BUTTONS_AMOUNT 18


const int buttons[BUTTONS_AMOUNT] = {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_0,
    BUTTON_1,
    BUTTON_2,
    BUTTON_3,
    BUTTON_4,
    BUTTON_5,
    BUTTON_6,
    BUTTON_7,
    BUTTON_8,
    BUTTON_9,
    BUTTON_START,
    BUTTON_STOP,
    BUTTON_BACK,
    BUTTON_ENTER
};


class IOController {
    private:

    public:
    IOController();

    bool buttonWait();
    void buttonCall(void(*fn)(), int pin);

    void buttonReset();
    void start();
    void end();

    
    
};


#endif