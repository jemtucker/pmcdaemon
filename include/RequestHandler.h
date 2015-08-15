//
//  RequestHandler.h
//  pmcdaemon
//
//  Created by Jem Tucker on 05/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__RequestHandler__
#define __pmcdaemon__RequestHandler__

#include <memory>

#include "CivetServer.h"

class Device;

class RequestHandler : public CivetHandler {
protected:
    std::shared_ptr<Device> device;
    
public:
    RequestHandler(Device *d): device(d) {}
    
    virtual bool handlePost(CivetServer *, struct mg_connection *) = 0;
};

#endif /* defined(__pmcdaemon__RequestHandler__) */
