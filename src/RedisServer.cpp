
#include "../include/RedisServer.h"
// Pull in STL first
#include <cstddef>  // for std::byte and other definitions

// Temporarily redefine 'byte' to prevent name clash with Windows headers
#define byte win_byte
#include <winsock2.h>
#include <ws2tcpip.h>
#undef byte  // Restore original meaning

#include <thread>

// #define _NO_CPPSTDLIB

#include <unistd.h>
#include <iostream>

#include <unistd.h>
#include "../include/RedisDatabase.h"
#include <vector>
#include <thread>
#include <cstring>
#include <signal.h>
using namespace std;
#include "../include/RedisCommandHandler.h"
// #include <netinet/in.h>
static RedisServer* globalServer=nullptr;

void signalHandler(int signum){
    if(globalServer){
         if(RedisDatabase::getInstance().dump("dump.my_rdb")){
        cout<<"Databade dumped to dump.my_rdb\n";
    }else{
        cerr<<"error dumpingg database\n";
    }
        cout<<"caught signal "<<signum<<" , shutting down ...\n";
        globalServer->shutdown();
    }
    exit(signum);
}
void RedisServer::setupSignalHandler(){
    signal(SIGINT,signalHandler);
}
RedisServer::RedisServer(int port):port(port),server_socket(-1),running(true){
    globalServer=this;
    setupSignalHandler();
}

void RedisServer::shutdown(){
     
    running=false;
    if(server_socket!=-1){
        close(server_socket);
    }
    cout<<"server shutdown complete"<<endl;
}

void RedisServer::run(){
    WSADATA ws;
    if(WSAStartup(MAKEWORD(2,2),&ws)<0){
        cout<<"WSA FAILED TO INITIALIZE "<<endl;

    }else{
        cout<<"WSA INITIALIZED"<<endl;
    }
    server_socket=socket(AF_INET,SOCK_STREAM,0);
    if(server_socket<0){
        cerr<<"Error creating Server Socket"<<endl;
        return;
    }

    int opt = 1;
    //call before bind function
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Error Binding Server Socket\n";
        return;
    }

    if (listen(server_socket, 10) < 0) {
        cerr << "Error Listening On Server Socket\n";
        return;
    } 

    cout << "Redis Server Listening On Port " << port << "\n";

    //command handler
    //Using threads so that we can manage multile clients at same time
    vector<std::thread> threads;
    RedisCommandHandler cmdHandler;
    while(running){
        int client_socket=accept(server_socket,nullptr,nullptr);
        if(client_socket<0){
            if(running){
                cerr<<"Error Accepting Client connection \n";
            
            }
            break;
        }

        //receiving client request

        threads.emplace_back([client_socket, &cmdHandler](){
            char buffer[1024];
            while (true) {
                memset(buffer, 0, sizeof(buffer));
                int bytes = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
                if (bytes <= 0) break;
                string request(buffer, bytes);
                string response = cmdHandler.processCommand(request);
                send(client_socket, response.c_str(), response.size(), 0);
            }
            close(client_socket);
        });
    }
    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }
    // WSACleanup();
    //shutdown
    //before shutdown persist the database

    if(RedisDatabase::getInstance().dump("dump.my_rdb")){
        cout<<"Databade dumped to dump.my_rdb\n";
    }else{
        cerr<<"error dumpingg database\n";
    }

}
