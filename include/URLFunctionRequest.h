//
//  URLFunctionRequest.h
//  pmcdaemon
//
//  Created by Jem Tucker on 07/09/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__URLFunctionRequest__
#define __pmcdaemon__URLFunctionRequest__

#include "Request.h"

class Configuration;

class URLFunctionRequest : public Request {
    Configuration *configuration;
public:
    URLFunctionRequest(const struct mg_request_info *i, Configuration *c);
    virtual int moduleType() override;
    
};

#endif /* defined(__pmcdaemon__URLFunctionRequest__) */
