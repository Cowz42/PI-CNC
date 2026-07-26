


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

#define STR2(x) #x
#define STR(y) STR2(y)

#define BUFFER_SIZE 256
#define BUFFER_SIZE_STR "" STR(BUFFER_SIZE)


#define SOCKET_NUM 15268



enum KEYS {
    X_P,
    Y_P,
    Z_P,
    A_P,
    B_P,
    C_B,
    R_S,
    F_N,
    L_S,
    E_S
};


char socketbuffer[BUFFER_SIZE];


int server_socket;

bool socketinit;
bool server = false;


struct sockaddr_in serv_addr;

Socket s;


struct sockaddr_in cli_addr;
int client_socket;



bool Socket::start(bool mode) {
    server = mode;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Socket Establishment failure\n";
        return false;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SOCKET_NUM);


    if (server) {
        int opt = 1;

        serv_addr.sin_addr.s_addr = INADDR_ANY;

        if (setsockopt(server_socket, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
            std::cerr << "Option set failure\n";
            return false;
        }

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
    } else {
        if (connect(server_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            std::cerr << "Connection Failure\n";
            return false;
        }
    }
    return true;
}


std::string Socket::recieve() {
    std::memset(socketbuffer, 0, BUFFER_SIZE);
    if (recv(server?client_socket:server_socket, socketbuffer, BUFFER_SIZE, 0) == -1) {
        return "";
    }
    return std::string(socketbuffer);
}

void Socket::transmit(std::string message) {
    if (!socketinit) {return;}
    send(server?client_socket:server_socket, message.data(), message.size(), 0);
}

void Socket::transmit(const char* message) {
    if (!socketinit) {return;}
    send(server?client_socket:server_socket, message, strlen(message), 0);
}

void Socket::end() {
    if (server) {
        close(client_socket);
    }
    close(server_socket);
    socketinit = false;
}



void sendVal(KEYS key, std::string value) {
    char b[BUFFER_SIZE];
    snprintf(b, BUFFER_SIZE, "%" BUFFER_SIZE_STR "s", value.data());
    s.transmit(b);
}