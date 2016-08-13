//
//  calls.cpp
//  Middleware
//
//  Created by Sathish Bowatta on 5/27/16.
//  Copyright © 2016 Sathish Bowatta. All rights reserved.
//

#include <iostream>
#include <netdb.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "calls.hpp"

int clientcall(int *sockfd, int portno, const char *address){
    struct sockaddr_in servaddr;
    struct hostent *server;
    
    //create client socket
    if((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        std::cerr << "Unable to open socket" << std::endl;
        //exit (EXIT_FAILURE);
	return 0;
    }
    
    if ((server = gethostbyname(address)) == 0){
        std::cerr << "Host does not exist" << std::endl;
       // exit (EXIT_FAILURE);
	return 0;
    }
    
    memset((char *) &servaddr,'0', sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    
    memcpy((char *)&servaddr.sin_addr.s_addr, (char *) server -> h_addr, server -> h_length);
    
    servaddr.sin_port = htons(portno);
    
    if ((connect(*sockfd,(struct sockaddr *) &servaddr, sizeof(servaddr))) < 0){
        std::cerr << "Unable to connect" << std::endl;
	return 0;
        //exit (EXIT_FAILURE);
    }
    return 1;
}

void servercall(int *sockfd, int portno, struct sockaddr_in *servaddr){
    //create server socket
    if((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        std::cerr << "Unable to open socket" << std::endl;
        exit (EXIT_FAILURE);
    }
    
    memset((char*)servaddr,'0', sizeof(struct sockaddr_in));

    (*servaddr).sin_family = AF_INET;
    (*servaddr).sin_addr.s_addr = INADDR_ANY;
    (*servaddr).sin_port = htons(portno);
    
    //bind socket
    if(bind(*sockfd, (struct sockaddr *)servaddr, sizeof(struct sockaddr_in)) < 0){
        std::cerr << "Unable to bind" << std::endl;
        exit (EXIT_FAILURE);
    }
    
    listen(*sockfd, 5);
}
