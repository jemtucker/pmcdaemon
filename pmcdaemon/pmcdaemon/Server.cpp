//
//  Server.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 04/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Server.h"
#include "Handlers.h"

Server::Server(Player *p) {
    char *options = nullptr;
    server = new CivetServer((const char **) &options);
    
    server->addHandler("/station/", new RadioHandler(p));
}