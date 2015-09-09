//
//  URLFunctionRequest.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 07/09/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "URLFunctionRequest.h"



URLFunctionRequest::URLFunctionRequest(const struct mg_request_info *i, Configuration *c): Request(i), configuration(c) {
    
}

int URLFunctionRequest::moduleType() {
    return 2; // TODO Use Enum
}