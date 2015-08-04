//
//  Server.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 04/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Server.h"

static const char *options[] = {
    "num_threads", "1",
    "listening_ports", "8080",
    NULL
};

void Server::init() {
    std::unique_ptr<CivetServer> cs(new CivetServer(options));
    server = std::move(cs);
}

void Server::addHandler(std::string route, CivetHandler &handler) {
    server->addHandler(route, handler);
}