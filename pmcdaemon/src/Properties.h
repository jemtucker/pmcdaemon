//
//  Properties.h
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Properties__
#define __pmcdaemon__Properties__

#include <stdio.h>
#include <string>
#include <map>

class Properties {
    std::map<std::string, std::string> map;
    
public:
    Properties(std::string);
    void parseLine(const char *);
    std::string getProperty(std::string);
};

#endif /* defined(__pmcdaemon__Properties__) */
