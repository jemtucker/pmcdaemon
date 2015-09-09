//
//  URLFunctionRequestHandler.h
//  pmcdaemon
//
//  Created by Jem Tucker on 07/09/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__URLFunctionRequestHandler__
#define __pmcdaemon__URLFunctionRequestHandler__

#include "RequestHandler.h"

class URLFunctionRequestHandler : public RequestHandler {
    int matchRequest(std::string uri);
public:
    URLFunctionRequestHandler(Device *d): RequestHandler(d) {}
    bool handlePost(CivetServer *, struct mg_connection *) override;
};

#endif /* defined(__pmcdaemon__URLFunctionRequestHandler__) */
