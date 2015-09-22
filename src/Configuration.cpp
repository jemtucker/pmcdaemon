//
//  Configuration.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Configuration.h"

#include <exception>
#include <iostream>

#define EMPTY_URL ""

std::string Configuration::getUrl(std::string name) {
    if (stations.count(name) < 1) return EMPTY_URL;
    return stations[name]->getUrl();
}

void Configuration::loadConfig(std::istream &instream) {
    std::string line;
    
    while (std::getline(instream, line)) {
        if (!line.length())
            continue;
        parseLine(line.c_str());
    }
}

void Configuration::parseLine(const char* line) {
    std::string k = "";
    std::string v = "";
    
    char c;
    int i = 0;
    bool iskey = true;
    
    while ((c = *(line + (i++))) != 0) {
        if (c == ' ')  continue;
        if (c == '\t') continue;
        if (c == '\n') {
            iskey = true;
            continue;
        }
        if (c == '=') {
            iskey = false;
            continue;
        }
        if (iskey) k += c;
        else v += c;
    }
    
    stations[k] = (std::unique_ptr<Station>(new Station::Station(k, v, (int) stations.size())));
}

std::vector<std::string> Configuration::getAllStations() {
    std::vector<std::string> allStations;
    for (auto iter = stations.begin(); iter != stations.end(); iter ++) {
        allStations.push_back(iter->first);
    }
    return allStations;
}



