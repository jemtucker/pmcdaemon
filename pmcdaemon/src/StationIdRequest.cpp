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

StationIdRequest::StationIdRequest(const struct mg_request_info *i): Request(i) {}

void StationIdRequest::execute(Device *device) {
    if (info->query_string != nullptr) {
        std::string string(info->query_string);
        std::string idString = string.substr(strlen(QUERY_ID));
        std::cout << "Recieved request to play station: "
        << idString
        << std::endl;
        device->play(RADIO, idString);
    } else {
        std::cout << "No query provided for execution." << std::endl;
    }
}
