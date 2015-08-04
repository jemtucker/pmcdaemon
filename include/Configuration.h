//
//  Configuration.h
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Configuration__
#define __pmcdaemon__Configuration__

#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <exception>

#include "Station.h"

class Configuration {
    std::vector<std::unique_ptr<Station>> stations;
    
    void loadConfig(const std::string &);
    void parseLine(const char *);
    
public:
    Configuration(const std::string &);
    std::string* getUrl(int);
};

#endif /* defined(__pmcdaemon__Configuration__) */
