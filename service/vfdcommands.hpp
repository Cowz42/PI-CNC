



#ifndef VFD_COMMAND_H
#define VFD_COMMAND_H


/**
 * VFD Packet Structure
 * 
 * 
 * Then will send a control code of two letters
 * Then a number if need be for the given command of a maximum of 10 digits decimal included
 * 
 * Total Packet Size will be 12 and 13 with the stop bit
 * 
 * Same Structure when transmitting to and from the device
 */








#ifdef __linux__
#include<cstring>
#include<cstdio>
#include<stdlib.h>
#endif

// Will send the error number as listed in the array below
#define ERROR "ER"


// Tells either device to stop completely, un-recoverable error
#define STOPALL "ST"


// Used to check if the other device is responding
#define PING "MS"
#define ACK "MR"



// Sent once the VFD reaches the appropriate Speed
#define SPEED_REACH "SR"



#define A_CH_START "AS"
#define A_CH_STOP "AO"
#define A_CH_SPEED "AR"
#define A_CH_SYNC "AP"
#define A_CH_MAX_SPEED "AV"
#define A_CH_MAX_ACCEL "AA"

#define B_CH_START "BS"
#define B_CH_STOP "BO"
#define B_CH_SPEED "BR"
#define B_CH_SYNC "BP"
#define B_CH_MAX_SPEED "BV"
#define B_CH_MAX_ACCEL "BA"


// Unsyncronized motor motion
#define NO_SYNC "NS"

// Syncronize A and B channel speeds
#define A_B_SYNC "AB"

// A will spin at some multiple of b faster
#define A_OVER_B_SYNC "SA"

// inverse of previous
#define B_OVER_A_SYNC "SB"




const char* error_codes[] {
    "Comm Fault",                       // 0
    "Over Current",                     // 1
    "Safety Fault",                     // 2
    "Power Failure",                    // 3
    "Invalid Packet",                   // 4
    "Channel A Disabled",               // 5
    "Channel B Disabled",               // 6
    "Speed Outside Range",              // 7
    "Invalid Position",                 // 8
    "Sync Error",                       // 9
    "Motor Not Detected",               // 10
    "Unknown, Rebooting",               // 11
    
};


const char* codes[] {
    ERROR,
    STOPALL,
    PING,
    ACK,
    SPEED_REACH,
    A_CH_START,
    A_CH_STOP,
    A_CH_SPEED,
    A_CH_SYNC,
    A_CH_MAX_SPEED,
    A_CH_MAX_ACCEL,
    B_CH_START,
    B_CH_STOP,
    B_CH_SPEED,
    B_CH_SYNC,
    B_CH_MAX_SPEED,
    B_CH_MAX_ACCEL,
    NO_SYNC,
    A_B_SYNC,
    A_OVER_B_SYNC,
    B_OVER_A_SYNC,
};


typedef struct {
    int code;
    float num;
} packet;

char numbervalue[11];


char packetbuffer[64];

int packetStrBuilder(packet p) {
    if ((unsigned int)p.code >= sizeof(codes)) {
        return -1;
    }
    if (p.code == 0) {
        if (p.num >= sizeof(error_codes)) {
            return -1;
        }
    }
    strcat(packetbuffer, codes[p.code]);
    sprintf(numbervalue, "%+10.3f", (double)p.num);
    strcat(packetbuffer, numbervalue);
    strcat(packetbuffer, "\n");
    return 0;
}

int findCode(const char* str) {
    for (unsigned int i = 0; i < sizeof(codes); i++) {
        if (codes[i][0] == str[0] && codes[i][1] == str[1]) {
            return i;
        }
    }
    return -1;
}

packet packetStrParser(char* str) {
    packet out;
    out.num = 0;
    out.code = 0;
    if (strlen(str) < 12) {
        return out;
    }
    out.code = findCode(str);
    out.num = atof(str + 2);
    return out;
}







#endif