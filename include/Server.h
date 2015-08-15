//
//  Server.h
//  pmcdaemon
//
//  Created by Jem Tucker on 04/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Server__
#define __pmcdaemon__Server__

#include <memory>

class CivetHandler;
class CivetServer;
class Device;

class Server {
    std::unique_ptr<CivetServer> server;
public:
    void init(Device *d);
    void addHandler(std::string, CivetHandler &);
};

#endif /* defined(__pmcdaemon__Server__) */
