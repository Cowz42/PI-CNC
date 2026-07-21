


#define SERVICE_SOCKET




#include"programrun.h"
#include"socketmanager.h"
#include<unistd.h>
#include<string>


int main(int argc, char** argv) {

    cnc.start();
    while(!s.start()) {
        usleep(15000);
    }

    s.transmit("Hello Client :)");

    std::string hello = s.recieve();

    s.transmit("Right back at you");
    s.transmit(hello);
    

    return 0;
}
