//
//  Server.h
//  pmcdaemon
//
//  Created by Jem Tucker on 04/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Server__
#define __pmcdaemon__Server__

#include <stdio.h>
#include <mutex>
#include <queue>

#include "CivetServer.h"
#include "Player.h"
#include "Request.h"

class Server {
    std::mutex mutexQueue;
    std::queue<Request> requestQueue;
    
    CivetServer *server;
    Player *player;
    
public:
    Server(Player *);
    void queueRequest(Request *);
};

#endif /* defined(__pmcdaemon__Server__) */
