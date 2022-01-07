
#include "Server.h"
#include <ctime>



Server::Server(int port) throw (const char*) {
    shouldStop=false;
    fd=socket(AF_INET,SOCK_STREAM,0);
    if(fd<0)
        throw "socket failed";

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if(bind(fd,(struct sockaddr*)&server, sizeof(server))<0)
        throw "bind failure";

    if(listen(fd, clientLimit)<0)
        throw "listen failure";
}


void sigHandler(int sigNum){
    //cout<<"sidH"<<endl;
}


void Server::start(ClientHandler& ch)throw(const char*){
    t=new thread([&ch,this](){
        signal(SIGALRM,sigHandler);
        while(!shouldStop){
            socklen_t clientSize=sizeof(client);
            alarm(1);
            int aClient = accept(fd,(struct sockaddr*)&client,&clientSize);

            if(aClient>0){
                ch.handle(aClient);
                close(aClient);
            }
            alarm(0);

        }
        close(fd);
    });
}

void Server::stop(){
    shouldStop = true;
	//t->join(); // do not delete this!
}

Server::~Server() {
}

