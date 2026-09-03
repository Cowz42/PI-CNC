

#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H


#include<string>
#include"netpacket.hpp"




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

    // Extra call for getLatestPacket cause I changed the call
    // and I also didn't want to re-write a bunch of other code
    static std::string recieve();

    // Gets the most recent packet sent from the other device
    static NetworkPacket getLatestPacket();

    // Search for a specific keys in the message
    static NetworkPacket searchPacket(std::string key);

    // clears the backlog of packets, and sends a reload command
    static void reloadSocket();

    // Function to send errors to the other program
    static void sendError(std::string msg);

    // Function to send log messages to the other program
    static void sendLog(std::string msg);
};

extern Socket net_socket;

#endif