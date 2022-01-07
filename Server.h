/*
 * Server.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Eli
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <pthread.h>
#include <thread>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include "CLI.h"
#include "CLI.cpp"

using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
    public:
    virtual void handle(int clientID)=0;
};


// you can add helper classes here and implement on the cpp file
class SocketIO:public DefaultIO {
    int fd;
public:
    SocketIO(int fd):fd(fd){}
    
    virtual string read(){
        char c=0;
        size_t i=0;
        string s="";
        while(c!='\n'){
            recv(fd,&c,sizeof(char),0);
            s+=c;
        }
        //cout << s;
        return s;
    }
    virtual void write(string text){
        const char* text2 = text.c_str();
        send(fd, text2, strlen(text2), 0);
    }

    virtual void write(float f){
        ostringstream ss;
        ss <<f;
        string s(ss.str());
        write(s);
    }

    virtual void read(float* f){
//        char buffer[1024];
//        int n = recv(fd, buffer, 100, 0);
//        return buffer;
    }

    ~SocketIO(){
    }
};

// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
	public:
        virtual void handle(int clientID){
            SocketIO* sio = new SocketIO(clientID);
            CLI* cli = new CLI(sio);
            cli->start();
    }
};


// implement on Server.cpp
class Server {
	thread* t; // the thread to run the start() method in

	// you may add data members
    bool shouldStop;
    int fd;
    int clientLimit = 3;
    sockaddr_in server;
    sockaddr_in client;

public:
	Server(int port) throw (const char*);
	virtual ~Server();
	void start(ClientHandler& ch)throw(const char*);
	void stop();
};

#endif /* SERVER_H_ */
