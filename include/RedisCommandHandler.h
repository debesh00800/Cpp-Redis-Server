
#ifndef REDIS_COMMAND_HANDLER_H
#define REDIS_COMMAND_HANDLER_H
#include <iostream>
// #include <its/stdc++.h>
using namespace std;

class RedisCommandHandler{
    public:
    RedisCommandHandler();

    //processing a command from client and return RESP-formatted message
    
    string processCommand(string &commandLine);
};
#endif