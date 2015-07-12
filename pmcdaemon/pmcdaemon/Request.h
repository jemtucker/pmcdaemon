//
//  Request.h
//  pmcdaemon
//
//  Created by Jem Tucker on 05/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Request__
#define __pmcdaemon__Request__

#include <stdio.h>

#include "CivetServer.h"
#include "Player.h"

class Request {
protected:
    const struct mg_request_info *info;
    Player *pmcplayer;
    
public:
    Request(Player *p, const struct mg_request_info *i) {
        pmcplayer = p;
        info = i;
    }
    virtual void execute() = 0;
};

#endif /* defined(__pmcdaemon__Request__) */
