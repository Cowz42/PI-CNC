




#include"programrun.h"




bool exit_flag = false;

GCodeParse g;

GCodeInstruction buffer;
Cmd ins;

long long prev;


Stepper x = Stepper(X_1, X_2, X_3, X_4, 1, 100);
Stepper y = Stepper(Y_1, Y_2, Y_3, Y_4, 1, 100);
Stepper z = Stepper(Z_1, Z_2, Z_3, Z_4, 1, 100);


StepperControl gantry;




long long timeInMicroseconds(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000000)+(tv.tv_usec);
}

long long deltaTime() {
    long long now = timeInMicroseconds();
    long long out = now - prev;
    prev = now;
    return out;
}




void step() {
    x.update();
    y.update();
    z.update();
}


void runIns() {
    gantry.setInstruction(ins);

    
    while(gantry.step((int)deltaTime())) {
        if (exit_flag) {
            return;
        }
        x.setPosition(gantry.getX());
        y.setPosition(gantry.getY());
        z.setPosition(gantry.getZ());
        step();
    }
    
    x.setPosition(gantry.getX());
    y.setPosition(gantry.getY());
    z.setPosition(gantry.getZ());
    step();
}

void GCodes() {
    switch (ins.num) {
        case 0:
            runIns();
            break;
        case 1:
            runIns();
            break;
        case 2:
            runIns();
            break;
        case 3:
            runIns();
            break;
        case 4:
            runIns();
            break;
        case 20:
            gantry.setImperial();
            break;
        case 21:
            gantry.setMetric();
            break;
        case 90:
            gantry.setAbsoluteCoordinate();
            break;
        case 91:
            gantry.setRelativeCoordinate();
            break;
        case 94:
            gantry.setF(ins.f);
            break;
        default:
            std::cout << "Un-supported G Code detected, ignoring\n";
            break;
    }
}

void MCodes() {
    switch (ins.num) {
        case 0:
            // Need io controller
            break;

    }
}


void CNC::startProgram(std::string name) {
    gantry.setMetric();

    g.set_working_file(name);


    // iterate throgh the commands in the given file
    
}

void CNC::start() {
    x.start();
    y.start();
    z.start();
    gantry.setAbsoluteCoordinate();
    gantry.home();
}

void CNC::run() {
    buffer = g.read_command();
    if (!(buffer._x || buffer._y || buffer._z || buffer._i || buffer._j || buffer._f || buffer._s)) {
        return;
    }
    ins = convert(buffer);
    if (ins.letter == 'G') {
        GCodes();
    } else if (ins.letter == 'M') {
        MCodes();
    } else {
        std::cout << "Invalid GCode\n";
    }
    
}