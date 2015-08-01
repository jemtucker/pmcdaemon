//
//  Module.h
//  pmcdaemon
//
//  Created by Jem Tucker on 17/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Module__
#define __pmcdaemon__Module__

#include <memory>
#include <string>

#include "Configuration.h"

class Module {
protected:
    std::shared_ptr<Configuration> configuration;
public:
    Module(std::shared_ptr<Configuration> c): configuration(c) {}
    virtual void init() = 0;
    /* Playing methods */
    virtual void play(std::string &) = 0;
    virtual void stop() = 0;
};

#endif /* defined(__pmcdaemon__Module__) */
