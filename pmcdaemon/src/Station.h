//
//  Station.h
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Station__
#define __pmcdaemon__Station__

#include <string>
#include <memory>

class Station {
    std::string name;
    std::string url;
    int identifier;
    
public:
    Station(std::string &, std::string &, int);
    void print();
    std::string* getUrl();
};

#endif /* defined(__pmcdaemon__Station__) */
