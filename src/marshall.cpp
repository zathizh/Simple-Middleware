//
//  marshall.cpp
//  Middleware
//
//  Created by Sathish Bowatta on 5/28/16.
//  Copyright © 2016 Sathish Bowatta. All rights reserved.
//

#include <string>
#include <string.h>
#include "marshall.hpp"

void marshall(Object *obj, char *buffer){
    char *ptr = (char *)obj;
    memset(buffer, 'o', sizeof(Object));    
    for (int i= 0; i < sizeof(Object); i++){
        buffer[i] =  *(ptr+i);
    }
}

void unmarshall(Object *obj, char *buffer){
    char *ptr = (char *)obj;
    memset(obj, '0', sizeof(Object)); 
    for (int i= 0; i< sizeof(Object); i++){
        *(ptr+i) =  buffer[i];
    }
}
