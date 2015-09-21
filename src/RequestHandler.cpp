//
//  RequestHandler.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 05/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "RequestHandler.h"

#include <iostream>
#include <regex>

#define QUERY_ID "id="
#define QUERY_REGEX "^id=.*$"

bool RequestHandler::handlePost(CivetServer *cs, struct mg_connection *conn) {
    const struct mg_request_info *info = mg_get_request_info(conn);
    
    switch (matchRequest(info->uri)) {
        case 0:
            break;
        case 1: {
            listAllStations(conn);
            break;
        }
        case 2: {
            mg_printf(conn, "Stopping playback");
            device->getStreamModule()->stop();
            break;
        }
        case 3: {
            mg_printf(conn, "Starting playback");
            std::string url = parseQueryString(info->query_string);
            device->getStreamModule()->playUrl(url);
            break;
        }
        default: {
            mg_printf(conn, "404 Not Found");
            break;
        }
    }
    
    
    
    return true;
}

int RequestHandler::matchRequest(std::string uri) {
    for (int i = 0; i < routes.size(); i++) {
        std::regex re(routes[i]);
        if (std::regex_match(uri, re)) {
            return i;
        }
    }
    return -1;
}

std::string RequestHandler::parseQueryString(std::string queryString) {
    std::regex regex(QUERY_REGEX);
    if (std::regex_match(queryString, regex)) {
        std::string idString = queryString.substr(strlen(QUERY_ID));
        std::cout << "Recieved request to play station: "
                  << idString
                  << std::endl;
        return device->getConfig()->getUrl(idString);
    } else {
        std::cout << "No valid query provided for execution." << std::endl;
        return "";
    }
}

void RequestHandler::listAllStations(struct mg_connection *conn) {
    auto stations = device->getConfig()->getAllStations();
    auto iter = stations.begin();
    
    std::string str = *iter;
    
    for (iter++; iter != stations.end(); iter++) {
        str.append(*iter + "\n");
    }
    
    mg_printf(conn, "%s", str.c_str());
}



