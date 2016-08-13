//
//  stringop.cpp
//  Middleware
//
//  Created by Sathish Bowatta on 5/28/16.
//  Copyright © 2016 Sathish Bowatta. All rights reserved.
//

#include <string>
#include <string.h>
#include "stringop.hpp"

std::string trim(std::string& str){
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last-first+1));
}
