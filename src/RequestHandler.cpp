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
        case 1:
            list(conn);
            break;
        case 2:
            stop(conn);
            break;
        case 3:
            play(conn, info);
            break;
        default:
            mg_printf(conn, "404 Not Found\n");
            break;
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
        return idString;
    } else {
        std::cout << "No valid query provided for execution." << std::endl;
        return "";
    }
}

void RequestHandler::list(struct mg_connection *conn) {
    auto stations = device->getConfig()->getAllStations();
    auto iter = stations.begin();
    
    std::string str = *iter;
    
    for (iter++; iter != stations.end(); iter++) {
        str.append(*iter + "\n");
    }
    
    mg_printf(conn, "%s", str.c_str());
}

void RequestHandler::stop(struct mg_connection *conn) {
    mg_printf(conn, "Stopping playback\n");
    device->getStreamModule()->stop();
}

void RequestHandler::play(struct mg_connection *conn, const struct mg_request_info *info) {
    mg_printf(conn, "Starting playback\n");
    std::string stationName = parseQueryString(info->query_string);
    std::string url = device->getConfig()->getUrl(stationName);
    device->getStreamModule()->playUrl(url);
}



