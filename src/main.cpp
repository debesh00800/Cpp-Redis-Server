#include <iostream>
#include "../include/RedisServer.h"
#include "../include/RedisDatabase.h"
using namespace std;
#include <thread>
#include <chrono>

// #include <thread>
int main(int argc, char* argv[]){

    //argc and argv helps to take input from terminal, for example ./main I am debesh
    // cout<<argc<<endl;
    // for(int i=0;i<argc;i++){
    //     cout<<argv[i]<<endl;
    // }

    int port=6379;
    if(argc>=2){
        port=stoi(argv[1]);
    }
    
    if(RedisDatabase::getInstance().load("dump.my_rdb")){
        cout<<"Database loadedfrom dump.my_rdb\n";
    }else{
        cout<<"No dump found or load failed, starting with an empty database\n";
        
    }
    RedisServer server(port);

    //background persistence, save inn database in ecvery 300 seconds

    thread persistanceThread([](){
        while(true){
            std::this_thread::sleep_for(std::chrono::seconds(300));
            //dump the database here
            if(!RedisDatabase::getInstance().dump("dump.my_rdb")){
                cerr<<"error dumping database\n";
            }else{
                cout<<"database dumped to dump.my_rdb\n";
            }

        }
    });
    persistanceThread.detach();
    server.run();


    return 0;
}