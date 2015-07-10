//
//  Configuration.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Configuration.h"

#include <fstream>
#include <iostream>
#include <exception>

#define EMPTY_URL ""

Configuration::Configuration(std::string *path): stations(new std::vector<ManagedStation>()) {
    loadConfig(path);
}

std::string* Configuration::getUrl(int i) {
    if (i > stations->size() - 1)
        throw new std::runtime_error("Attempted to access a station ID that does not exist");
    return stations->operator[](i)->getUrl();
}

void Configuration::loadConfig(std::string *path) {
    std::ifstream file(path->c_str());
    std::string line;
    
    while (std::getline(file, line)) {
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
    
    stations->push_back(std::unique_ptr<Station>(new Station::Station(new std::string(k), new std::string(v), (int) stations->size())));
}



