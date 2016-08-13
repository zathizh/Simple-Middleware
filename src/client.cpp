//
//  main.cpp
//  Client
//
//  Created by Sathish Bowatta on 5/27/16.
//  Copyright © 2016 Sathish Bowatta. All rights reserved.
//

#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "calls.hpp"
#include "objects.hpp"
#include "linkedlist.hpp"
#include "marshall.hpp"

int connfd;

int main (int argc, char *argv[]){
    int sockfd;
    
    //LinkedList *dataStore = initLinkedLst();
    
    if(argc < 3){
        std::cerr << "usage : client host port" << std::endl;
        return 0;
    }
    
    clientcall(&sockfd, atoi(argv[2]), argv[1]);
    
    time_t timer;
    time(&timer);
    
    int seqID = -1;
    
    Object request("Request", (argc==4)?argv[3]:"Service1");
    //pushToLinkedList(dataStore, request);
 
    char reqBuffer[sizeof(Object)];
    marshall(&request, reqBuffer);

    //write(sockfd, (char *)&request, sizeof(Object));
    write(sockfd, (char *)reqBuffer, sizeof(Object));
    read(sockfd, (int *)&seqID, sizeof(int));
    if (!(request.getSeqID() == seqID)){
        std::cout << "Error : Delivering Message" << std::endl;
    }
    else{
        //std::cout << "Message Delivered" << std::endl;
        //deleteFromLinkedList(dataStore, request);

	char resBuffer[sizeof(Object)];
	memset(resBuffer, '0', sizeof(Object));
        
        Object response;
//        memset(&response, '0', sizeof(Object));
        
        //read(sockfd, (char *)&response, sizeof(Object));
        read(sockfd, (char *)resBuffer, sizeof(Object));

	unmarshall(&response, resBuffer);  
      
        seqID = response.getSeqID();
        write(sockfd,  (int *)&seqID, sizeof(int));
        
        response.print();
    }
    close(sockfd);
    return 0;
}

