
#ifndef REDIS_SERVER_H
#define REDIS_SERVER_H
#include <iostream>
// #include <bits/stdc++.h>
#include <string>
#include <atomic>
using namespace std;
//use of ifndef and hou .h file is defines

class RedisServer{
public:
RedisServer(int port);
void run();
void shutdown();

private:
int port;
int server_socket;
atomic<bool> running;

//setup signal handaling for graceful shutdown(ctrl+ c)
void setupSignalHandler();

};

#endif