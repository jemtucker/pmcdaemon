//
//  Request.h
//  pmcdaemon
//
//  Created by Jem Tucker on 05/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Request__
#define __pmcdaemon__Request__

#include "CivetServer.h"
#include "Device.h"
#include "Module.h"

class Request {
protected:
    const struct mg_request_info *info;
    
public:
    Request(const struct mg_request_info *i) {
        info = i;
    }
    
    virtual void execute(Device *) = 0;
};

#endif /* defined(__pmcdaemon__Request__) */
