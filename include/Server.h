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
#include <thread>

#include "CivetServer.h"
#include "Request.h"

class Server {
    std::unique_ptr<CivetServer> server;
    std::unique_ptr<Request> getNextRequest();
    
public:
    void init();
    void addHandler(std::string, CivetHandler &);
};

#endif /* defined(__pmcdaemon__Server__) */
