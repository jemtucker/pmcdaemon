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
#include <memory>
#include <chrono>

#include "CivetServer.h"
#include "Player.h"
#include "Request.h"

struct ServerSettings {
    const char **civetOptions;
    std::chrono::milliseconds workInterval;
};

class Server {
    struct ServerSettings settings;
    
    std::unique_ptr<CivetServer> server;
    
    std::mutex mutexQueue;
    std::queue<std::unique_ptr<Request>> requestQueue;
    std::unique_ptr<std::thread> worker;
    
    void startWorker();
    void doWork();
    std::unique_ptr<Request> getNextRequest();
    
public:
    Server(Player *);
    void queueRequest(Request *);
};

#endif /* defined(__pmcdaemon__Server__) */
