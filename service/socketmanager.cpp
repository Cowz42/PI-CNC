


#include"socketmanager.h"
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string>
#include<cstring>
#include<stdlib.h>
#include<unistd.h>

#define BUFFER_SIZE 256
#define SOCKET_NUM 9001


char socketbuffer[BUFFER_SIZE];


int server_socket;

bool socketinit;


struct sockaddr_in serv_addr;

Socket s;

#ifndef CLIENT_SOCKET
#define CLIENT_SOCKET
#endif


#ifdef SERVICE_SOCKET

struct sockaddr_in cli_addr;
int client_socket;

bool Socket::start() {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Socket Establishment failure\n";
        return false;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SOCKET_NUM);

    if (bind(server_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Unable to bind socket\n";
        return false;
    }

    listen(server_socket, 1);

    int c = sizeof(struct sockaddr_in);

    client_socket = accept(server_socket, (struct sockaddr*)&cli_addr, (socklen_t*)&c);

    if (client_socket < 0) {
        std::cerr << "Client connection failure\n";
        return false;
    }

    if (recv(client_socket, socketbuffer, BUFFER_SIZE, 0) == -1) {
        std::cerr << "Invalid packet\n";
        return false;
    }
    if (socketbuffer[0] != 'V') {
        std::cerr << "Invalid connection\n";
        return false;
    }

    socketinit = true;
    return true;
}


std::string Socket::recieve() {
    std::memset(socketbuffer, 0, BUFFER_SIZE);
    if (recv(client_socket, socketbuffer, BUFFER_SIZE, 0) == -1) {
        return "";
    }
    return std::string(socketbuffer);
}

void Socket::transmit(std::string message) {
    if (!socketinit) {return;}
    send(client_socket, message.data(), message.size(), 0);
}

void Socket::transmit(const char* message) {
    if (!socketinit) {return;}
    send(client_socket, message, strlen(message), 0);
}

void Socket::end() {
    close(client_socket);
    close(server_socket);
    socketinit = false;
}


#else
#ifdef CLIENT_SOCKET

bool Socket::start() {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Socket Establishment failure\n";
        return false;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SOCKET_NUM);

    if (connect(server_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failure\n";
        return false;
    }

    char* start = "Version Alpha, bing chillin";

    if (send(server_socket, start, strlen(start), 0) < 0) {
        std::cerr << "Send Failure, being sad :(\n";
        return false;
    }
}


std::string Socket::recieve() {
    std::memset(socketbuffer, 0, BUFFER_SIZE);
    if (recv(server_socket, socketbuffer, BUFFER_SIZE, 0) == -1) {
        return "";
    }
    return std::string(socketbuffer);
}

void Socket::transmit(std::string message) {
    if (!socketinit) {return;}
    send(server_socket, message.data(), message.size(), 0);
}

void Socket::transmit(const char* message) {
    if (!socketinit) {return;}
    send(server_socket, message, strlen(message), 0);
}

void Socket::end() {
    close(server_socket);
    socketinit = false;
}


#else
#error "Specify what socket is being compilied"
#endif
#endif


