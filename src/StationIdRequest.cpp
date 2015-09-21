//
//  StationIdRequest.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 05/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include <iostream>
#include <exception>
#include <regex>

#include "Dispatcher.h"
#include "StationIdRequest.h"

#define QUERY_ID "id="
#define QUERY_REGEX "^id=.*$"

StationIdRequest::StationIdRequest(const struct mg_connection *conn, Configuration *conf): Request(conn) {
    configuration = conf;
}

int StationIdRequest::moduleType() {
    return ModuleType::URL_STREAM;
}

std::string StationIdRequest::url() {
    const struct mg_request_info *info = mg_get_request_info(connection);
    std::regex regex(QUERY_REGEX);
    if (info->query_string != nullptr &&
        std::regex_match(info->query_string, regex)) {
        
        std::string string(info->query_string);
        std::string idString = string.substr(strlen(QUERY_ID));
        
        std::cout << "Recieved request to play station: "
                  << idString
                  << std::endl;
        return configuration->getUrl(idString);
    } else {
        std::cout << "No valid query provided for execution." << std::endl;
        return "";
    }
}
