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
#include "Device.h"

class RequestHandler : public CivetHandler {
protected:
    std::shared_ptr<Device> device;
    
public:
    RequestHandler(Device *d): device(d) {}
    
    virtual bool handlePost(CivetServer *cs, struct mg_connection *conn) override;
};

#endif /* defined(__pmcdaemon__RequestHandler__) */
