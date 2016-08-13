//
//  objects.hpp
//  Middleware
//
//  Created by Sathish Bowatta on 5/27/16.
//  Copyright © 2016 Sathish Bowatta. All rights reserved.
//

#ifndef objects_hpp
#define objects_hpp


class Object{
private:
    std::string params;
    int seqID;
    std::string service;
public:
    Object(){}
    Object(std::string params, std::string service):params(params), service(service){}
    int getSeqID(){return this->seqID;}
    std::string getParams(){return this->params;}
    std::string getService(){return this->service;}
    void setSeqID(int);
    void setParams(std::string);
    void setService(std::string);
    void print();
};

#endif /* objects_hpp */
