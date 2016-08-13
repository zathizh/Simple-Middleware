//
//  main.cpp
//  Middleware
//
//  Created by Sathish Bowatta on 5/27/16.
//  Copyright © 2016 Sathish Bowatta. All rights reserved.
//

#include <arpa/inet.h>
#include <iostream>
#include <map>
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
#include "services.hpp"
#include "linkedlist.hpp"
#include "marshall.hpp"

int connfd;

int main(int argc, char * argv[]){
    
    std::map<std::string, Services> repo = initServices("./conf/services.conf");
    
    LinkedList *dataStore = initLinkedLst();
    
    int sockfd, portNo;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    
    
    portNo = (argc==2)?atoi(argv[1]):3456;
    
    servercall(&sockfd, portNo, &serv_addr);
    
    std::cout << "MIDDLEWARE RUNS ON PORT " << portNo << std::endl;
    
    for (;;){
        if ((connfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen))< 0){
            std::cerr << "Error : Unable to accept" << std::endl;
            return 0;
        }
        else{
            char clnt_name[INET_ADDRSTRLEN];
            
            inet_ntop(AF_INET,&cli_addr.sin_addr.s_addr,clnt_name,sizeof(clnt_name));
            
            char cReqBuffer[sizeof(Object)];
            memset(cReqBuffer, '0', sizeof(Object));
            
            Object cReq;
            int seqID = -1;
            
            //            memset (&cReq, '0', sizeof(Object));
            
            //read(connfd, (char *)&cReq, sizeof(Object));
            read(connfd, (char *)cReqBuffer, sizeof(Object));
            
            unmarshall(&cReq, cReqBuffer);
            
            seqID = cReq.getSeqID();
            
            pushToLinkedList(dataStore, cReq);
            
            write(connfd, (int *)&seqID, sizeof(int));
            seqID = -1;
            
            if (repo.find(cReq.getService()) != repo.end()){
                Services host;
                host = repo[cReq.getService()];
                std::cout << clnt_name << ":" << portNo << " -> " << host.getIP() << ":" << host.getPort() << "\t";
                
                int ser_sockfd;
                
                
                const char *ser = repo[cReq.getService()].getIP().c_str();
                int prt = repo[cReq.getService()].getPort();
                
                if(clientcall(&ser_sockfd, prt, ser)){
                    
                    //write(ser_sockfd, (char *)&cReq, sizeof(Object));
                    write(ser_sockfd, (char *)cReqBuffer, sizeof(Object));
                    read(ser_sockfd, (int *)&seqID, sizeof(int));
                    
                    if (!(cReq.getSeqID() == seqID)){
                        std::cout << "Error : Delivering" << std::endl;
                    }
                    else{
                        std::cout << "Delivered" << std::endl;
                        deleteFromLinkedList(dataStore, cReq);
                    }
                    
                    char resBuffer[sizeof(Object)];
                    memset(resBuffer, '0', sizeof(Object));
                    
                    Object response;
                    //memset (&response, '0', sizeof(Object));
                    seqID =-1;
                    
                    
                    //read(ser_sockfd, (char *)&response, sizeof(Object));
                    read(ser_sockfd, (char *)resBuffer, sizeof(Object));
                    
                    unmarshall(&response, resBuffer);
                    
                    pushToLinkedList(dataStore, response);
                    
                    seqID = response.getSeqID();
                    write(ser_sockfd, (int *)&seqID, sizeof(int));
                    
                    seqID = -1;
                    
                    //write(connfd, (char *)&response, sizeof(Object));
                    write(connfd, (char *)resBuffer, sizeof(Object));
                    read(connfd, (int *)&seqID, sizeof(int));
                    
                    std::cout << clnt_name << ":" << portNo << " <- " << host.getIP() << ":" << host.getPort() << "\t";
                    
                    if (!(response.getSeqID() == seqID)){
                        std::cout << "Error : Delivering" << std::endl;
                    }
                    else{
                        std::cout << "Delivered" << std::endl;
                        deleteFromLinkedList(dataStore, response);
                    }
                }
                else{
                    char errBuffer[sizeof(Object)];
                    memset(errBuffer, '0', sizeof(Object));
                    
                    Object error("Unable to connet to ", "Server");
                    marshall(&error, errBuffer);
                    
                    write(connfd, (char *)errBuffer, sizeof(Object));
                }
                
            }
            else{
		char errBuffer[sizeof(Object)];
                memset(errBuffer, '0', sizeof(Object));

                Object error("Unable to find the", "Service");
                marshall(&error, errBuffer);

                write(connfd, (char *)errBuffer, sizeof(Object));
                std::cout << "Error : Unable to Find the service. Service Unkown" << std::endl;
            }
        }
        close(connfd);
    }
    close(sockfd);
    return 0;
}



