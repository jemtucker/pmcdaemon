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
#include "Dispatcher.h"
#include "Server.h"

class Device {
    Configuration config;
    std::unique_ptr<Server> server;
    std::unique_ptr<Dispatcher> dispatcher;
    
public:
    Device();
    void init();
    Dispatcher *getDispatcher();
    Configuration *getConfig();
};

#endif /* defined(__pmcdaemon__Device__) */
