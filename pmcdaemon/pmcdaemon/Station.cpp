//
//  Station.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Station.h"
#include <iostream>

Station::Station(std::string *name, std::string *url,
                 int identifier): name(name), url(url), identifier(identifier) {}

std::string* Station::getUrl() {
    return url.get();
}

void Station::print() {
    std::cout << "  ID: " << identifier << std::endl;
    std::cout << "Name: " << name.get() << std::endl;
    std::cout << " URL: " << url.get()  << std::endl;
}