#include "rocket.h"

enum send_when {
    NEVER,
    ALWAYS,
    REGULAR
};

void handleDataStreams();
void initProtocol();
void sendMsg(rocket::MessageBase*, enum send_when);