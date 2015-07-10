//
//  Configuration.h
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Configuration__
#define __pmcdaemon__Configuration__

#include <stdio.h>
#include <string>
#include <memory>
#include <vector>

#include "Buffer.h"
#include "Station.h"

typedef std::unique_ptr<Station> ManagedStation;
typedef std::unique_ptr<std::vector<ManagedStation>> ManagedStations;

class Configuration {
    ManagedStations stations;
    
    void loadConfig(std::string *);
    void parseLine(const char *);
    
public:
    Configuration(std::string *);
    std::string* getUrl(int);
};

#endif /* defined(__pmcdaemon__Configuration__) */
