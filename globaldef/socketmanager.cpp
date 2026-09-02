


#include"socketmanager.hpp"
#include"netpacket.hpp"
#include<iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<vector>



#define STR2(x) #x
#define STR(y) STR2(y)

#define BUFFER_SIZE 256
#define BUFFER_SIZE_STR "" STR(BUFFER_SIZE)


#define PORT_NUM 15268

void prgm_error(std::string) {};
void prgm_log(std::string) {};



int connection_fd;
int new_socket;

struct sockaddr_in address;
socklen_t addrlen;

int opt = 1;


char recieve_buffer[BUFFER_SIZE];
char transmit_buffer[BUFFER_SIZE];

std::vector<std::string> packet_buffer;

bool config;


// internal transmits for the server and client respectivly
void transmitServer(const char* msg) {
    send(new_socket, transmit_buffer, strlen(transmit_buffer), 0);
}

void transmitClient(const char* msg) {
    send(connection_fd, transmit_buffer, strlen(transmit_buffer), 0);
}

bool startServer() {

    // Create the file descriptor for the socket
    if ((connection_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        prgm_error("Socket init failed\n");
        return false;
    }

    // Attaching the socket to the port
    if (setsockopt(
        connection_fd,
        SOL_SOCKET,
        SO_REUSEADDR | SO_REUSEPORT,
        &opt,
        sizeof(opt)
    )) {
        prgm_error("Socket Failed\n");
        return false;
    }

    // Configure things
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT_NUM);


    // Binding socket
    if (bind(
        connection_fd,
        (struct sockaddr*)&address,
        sizeof(address)
    ) < 0) {
        prgm_error("Bind Error\n");
        return false;
    }

    // Listen for the other device to connect
    if (listen(connection_fd, 3) < 0) {
        prgm_error("No Connection Started\n");
        return false;
    }


    if ((new_socket = accept(
        connection_fd,
        (struct sockaddr*)&address,
        &addrlen)
    ) < 0) {
        prgm_error("Acceptance Failure\n");
        return false;
    }

    prgm_log("Network Port Start Successful @");
    prgm_log(std::to_string(PORT_NUM));
    prgm_log(", Starting Control\n");

    return true;
}

bool startClient() {

    // Setup the socket file descriptor
    if ((connection_fd = 
    socket(
        AF_INET,
        SOCK_STREAM,
    0)) < 0) {
        prgm_error("Socket Creation Error\n");
        return false;
    }

    // Configure the port
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT_NUM);

    // IP stuff ig idk
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) {
        prgm_error("Address not supported, I have no idea what this does, but it was on geeks for geeks\n");
        return false;
    }

    // I also don't know what this does, but I don't remember how evaluating
    // within setting a varible works
    int status;

    // Set up the connection to the server
    if ((status = 
        connect(
            connection_fd,
            (struct sockaddr*)&address,
            sizeof(address)
        )
    ) < 0) {
        prgm_error("Connection Failed\n");
        return false;
    }

    prgm_log("Connection to the server started, yapping time\n");

    return true;
}

void autoParseBuffer() {

}

bool Socket::start(bool mode) {
    config = mode;

    addrlen = sizeof(address);

    if (config) {
        return startServer();
    }
    return startClient();
    
}

void Socket::end() {
    if (config == true) {
        close(new_socket);
    }
    close(connection_fd);
}

void Socket::transmit(std::string msg) {
    if (config) {
        transmitServer(msg.data());
        return;
    }
    transmitClient(msg.data());
}

void Socket::transmit(const char* msg) {
    if (config) {
        transmitServer(msg);
        return;
    }
    transmitClient(msg);
}

std::string Socket::getLatestPacket() {
    int ret_val = 0;
    do {
        ret_val = recv(new_socket, recieve_buffer, BUFFER_SIZE, 0);
        if (ret_val == -1) {
            prgm_error("Socket Read Error\n");
            return;
        }
        autoParseBuffer();
    } while(ret_val == 0);
}

std::string Socket::recieve() {
    return getLatestPacket();
}

std::string Socket::searchPacket(std::string key) {

}

void Socket::reloadSocket() {

};