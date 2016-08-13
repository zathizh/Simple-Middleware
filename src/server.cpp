//
//  main.cpp
//  Server
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

int main(int argc, char *argv[]){
    int sockfd, seqID;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    char clnt_name[INET_ADDRSTRLEN];

    //LinkedList *dataStore = initLinkedLst();
    
    //default server port is 1234
    servercall(&sockfd, atoi(argv[1]), &serv_addr);
    
    for (;;){
        if ((connfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) < 0){
            std::cerr << "Error : Unable to accept" << std::endl;
            return 0;
        }
        else{
            
            if(inet_ntop(AF_INET,&cli_addr.sin_addr.s_addr,clnt_name,sizeof(clnt_name)) != 0){
                std::cout << clnt_name << "\t";
            }
	    char cReqBuffer[sizeof(Object)];
	    memset(cReqBuffer, '0', sizeof(Object));

            Object cReq;
            //read(connfd, (char *)&cReq, sizeof(Object));
            read(connfd, (char *)cReqBuffer, sizeof(Object));

	    unmarshall(&cReq , cReqBuffer);

            seqID = cReq.getSeqID();
            write(connfd, (int *)&seqID, sizeof(int));
            
            Object response("Response", "From Server");
            //pushToLinkedList(dataStore,response);
            seqID = -1;
		
	    char resBuffer[sizeof(Object)];
	    marshall(&response, resBuffer);

            //write(connfd, (char *)&response, sizeof(Object));
            write(connfd, (char *)resBuffer, sizeof(Object));
            read(connfd, (int *)&seqID, sizeof(int));
            if (!(response.getSeqID() == seqID)){
                std::cout << "Error : Delivering Message" << std::endl;
            }
            else{
                std::cout << "Delivered" << std::endl;
                //deleteFromLinkedList(dataStore, response);
            }
            close(connfd);
        }
    }
    close(sockfd);
    return 0;
}
