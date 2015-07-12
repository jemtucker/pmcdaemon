//
//  RequestHandler.h
//  pmcdaemon
//
//  Created by Jem Tucker on 05/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__RequestHandler__
#define __pmcdaemon__RequestHandler__

#include <stdio.h>
#include <mutex>

#include "CivetServer.h"
#include "Server.h"

class RequestHandler : public CivetHandler {
protected:
    Server *pmcserver;
    Player *pmcplayer;
    
public:
    RequestHandler(Server *s, Player *p) {
        pmcserver = s;
        pmcplayer = p;
    }
    
    virtual bool handlePost(CivetServer *, struct mg_connection *) = 0;
};

#endif /* defined(__pmcdaemon__RequestHandler__) */
