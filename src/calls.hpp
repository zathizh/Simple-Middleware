//
//  calls.hpp
//  Middleware
//
//  Created by Sathish Bowatta on 5/27/16.
//  Copyright © 2016 Sathish Bowatta. All rights reserved.
//

#ifndef calls_hpp
#define calls_hpp

//void clientcall(int *, int, const char *);
int clientcall(int *, int, const char *);

void servercall(int *, int, struct sockaddr_in *);

#endif /* calls_hpp */
