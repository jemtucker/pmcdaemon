//
//  Server.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 04/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Server.h"

#include "Device.h"
#include "Module.h"

/* Request Handlers */
#include "StationRequestHandler.h"

Server::Server(Device *device) {
    const char *options[] = {
        "num_threads", "1",
        "listening_ports", "8080",
        NULL
    };
    
    std::unique_ptr<CivetServer> cs(new CivetServer(options));
    server = std::move(cs);
    
    server->addHandler("/station/", new StationRequestHandler(device));
}