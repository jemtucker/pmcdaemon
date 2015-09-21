//
//  Server.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 04/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Server.h"

#include "CivetServer.h"
#include "Device.h"
#include "RequestHandler.h"
#include "URLFunctionRequestHandler.h"

static const char *options[] = {
    "num_threads", "1",
    "listening_ports", "8080",
    NULL
};

void Server::init(Device *d) {
    std::unique_ptr<CivetServer> cs(new CivetServer(options));
    server = std::move(cs);
    
    server->addHandler("/api/play/", new RequestHandler(d));
    server->addHandler("/api/", new URLFunctionRequestHandler(d));
}