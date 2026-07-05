




#include"iocontroller.h"


IOController::IOController() {
    


}

void IOController::start() {
    wiringPiSetup();
    pcf8574Setup(v1, VIRTUAL_PORTA);
    pcf8574Setup(v9, VIRTUAL_PORTB);
    pcf8574Setup(v17, VIRTUAL_PORTC);

    for (int i = 0; i < BUTTONS_AMOUNT; i++) {
        pinMode(buttons[i], INPUT);
    }
}

