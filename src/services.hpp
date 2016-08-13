//
//  services.hpp
//  Middleware
//
//  Created by Sathish Bowatta on 5/27/16.
//  Copyright © 2016 Sathish Bowatta. All rights reserved.
//

#ifndef services_hpp
#define services_hpp

class Services{
private:
    std::string ip;
    int port;
public:
    Services(){}
    Services(std::string ip, int port):ip(ip), port(port){}
    std::string getIP(){return this->ip;}
    int getPort(){return this->port;}
};

std::map<std::string, Services> initServices(std::string);

#endif /* services_hpp */
