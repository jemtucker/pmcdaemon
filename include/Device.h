//
//  Device.h
//  pmcdaemon
//
//  Created by Jem Tucker on 17/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Device__
#define __pmcdaemon__Device__

#include <memory>

#include "Configuration.h"
#include "URLStreamModule.h"
#include "CivetServer.h"

static const char *OPTIONS[] = {
    "num_threads", "1",
    "listening_ports", "8080",
    NULL
};

class Device {
    Configuration config;
    std::unique_ptr<CivetServer> server;
    std::unique_ptr<URLStreamModule> streamModule;
    
public:
    Device();
    void init();
    URLStreamModule* getStreamModule();
    Configuration* getConfig();
};

#endif /* defined(__pmcdaemon__Device__) */
