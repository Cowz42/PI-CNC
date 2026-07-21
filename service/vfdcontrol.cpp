


#include"vfdcontrol.h"



int openPort(const char* name) {
    int n = open(name, O_RDWR | O_NOCTTY | O_SYNC);
    if (n < 0) {
        std::cerr << "Error opening port: " << name << ": " << strerror(errno) << std::endl;
        return -1;
    }
    return n;
}

bool configPort(int n, int speed) {
    struct termios tty;
    if (tcgetattr(n, &tty)) {
        std::cerr << "Error Configuring port: " << strerror(errno) << std::endl;
        return false;
    }
    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag | ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 5;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(n, TCSANOW, &tty) != 0) {
        std::cerr << "Error from tcsetattr: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}


int openPort() {
    vfd_fd = openPort(portname);
    if (vfd_fd < 0) {
        return 1;
    }

    if (!configPort(vfd_fd, B9600)) {
        close(vfd_fd);
        return 1;
    }

    return 0;
}



char* readPort() {
    int n = read(vfd_fd, vfdbuffer_recieve, sizeof(vfdbuffer_recieve));
    if (n < 0) {
        std::cerr << "Error reading from port: " << strerror(errno) << std::endl;
    }
    return vfdbuffer_recieve;
}

int writePort(const char* send) {
    if (write(vfd_fd, send, strlen(send)) < 0) {
        std::cerr << "Error writing to port: " << strerror(errno) << std::endl;
        return -1;
    }
    return 0;
}

void closePort() {
    close(vfd_fd);
}

int writePacket(packet p) {
    if (packetStrBuilder(p) != 0) {
        return -1;
    }
    return writePort(packetbuffer);
}