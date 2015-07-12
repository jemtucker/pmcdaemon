//
//  StationIdRequest.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 05/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include <iostream>
#include <exception>

#include "StationIdRequest.h"

#define QUERY_ID "id="

void StationIdRequest::execute() {
    std::string string(info->query_string);
    std::string idString = string.substr(strlen(QUERY_ID));
    
    try {
        int id = std::stoi(idString);
        std::cout << "Recieved request to play station: "
                  << id
                  << std::endl;
        pmcplayer->play(id);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}
