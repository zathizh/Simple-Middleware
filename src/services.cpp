//
//  services.cpp
//  Middleware
//
//  Created by Sathish Bowatta on 5/27/16.
//  Copyright © 2016 Sathish Bowatta. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>

#include "services.hpp"

std::map<std::string, Services> initServices(std::string serviceFileName){
    std::map<std::string, Services> repo;
    std::string line;
    
    std::ifstream serviceFile;
    serviceFile.open(serviceFileName.c_str());
    if (serviceFile.is_open()){
        while(getline(serviceFile, line)){
            std::string srvce, srvip, prt;
        
            std::istringstream is(line);
            is >> srvce;
	    if (srvce[0]!='#'){	
                is >> srvip;
                is >> prt;
                repo[srvce] = Services(srvip, atoi(prt.c_str()));
            }
        }
    }
    serviceFile.close();
    return repo;
}
