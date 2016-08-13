//
//  objects.cpp
//  Middleware
//
//  Created by Sathish Bowatta on 5/27/16.
//  Copyright © 2016 Sathish Bowatta. All rights reserved.
//

#include <iostream>
#include <string>

#include "objects.hpp"


void Object::setSeqID(int seqID){
    this->seqID = seqID;
}
void Object::setParams(std::string params){
    this->params = params;
}
void Object::setService(std::string service){
    this->service = service;
}
void Object::print(){
    std::cout << this->params << " " << this->service  << std::endl;
}
