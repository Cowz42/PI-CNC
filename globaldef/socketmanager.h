

#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H


#include<string>


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



class Socket {
    public:
    // Starts the port and awaits response, returns false if it fails
    // mode being true sets the socket to server mode, false is for the client
    static bool start(bool mode);

    // Exits the port and frees memory
    static void end();

    // Sends a string packet, of either a std::string or char*
    static void transmit(std::string msg);
    // Sends a string packet, of either a std::string or char*
    static void transmit(const char*);

    // Gets the most recent packet sent from the other device
    static std::string getLatestPacket();

    // Search for a specific keys in the message
    static std::string searchPacket(std::string key);

    // clears the backlog of packets, and sends a reload command
    static void reloadSocket();
};

extern Socket s;

#endif