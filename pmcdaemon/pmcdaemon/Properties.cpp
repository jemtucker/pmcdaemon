//
//  Properties.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Properties.h"
#include <fstream>

Properties::Properties(std::string path) {
    std::ifstream file(path.c_str());
    std::string line;
    while (std::getline(file, line)) {
        if (!line.length()) continue;
        parseLine(line.c_str());
    }
}

void Properties::parseLine(const char * line) {
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
        if (iskey) k.append(&c);
        else v.append(&c);
    }
    map[k] = v;
}