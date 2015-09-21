//
//  URLFunctionRequestHandler.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 07/09/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "URLFunctionRequestHandler.h"

#include <regex>
#include <iostream>

#include "StationIdRequest.h"

bool URLFunctionRequestHandler::handlePost(CivetServer *s, struct mg_connection *conn) {
    auto *info = mg_get_request_info(conn);
    std::string requestUri = info->uri;
    switch (matchRequest(requestUri)) {
        case 1:
            mg_printf(conn, "HTTP/1.1 200 OK\n\n%s\n", "now playing - ");
            break;
        case 2:
            mg_printf(conn, "HTTP/1.1 200 OK\n\n%s\n", "list all");
            break;
        case 3:
            mg_printf(conn, "HTTP/1.1 200 OK\n\n%s\n", "Stopping");
            device->getDispatcher()->dispatch(new StationIdRequest(conn, device->getConfig()));
            break;
        default:
            mg_printf(conn, "HTTP/1.1 404 Not Found\n\n");
            break;
    }
    
    //mg_printf(conn, "HTTP/1.1 200 OK\n\nRequest Queued\n%s", info->uri);
    
    return true;
}

int URLFunctionRequestHandler::matchRequest(std::string uri) {
    std::regex regexNowPlaying(R"(^\/api\/nowplaying$)");
    std::regex regexListAll(R"(^\/api\/listall$)");
    std::regex regexStop(R"(^\/api\/stop$)");
    
    if (std::regex_match(uri, regexNowPlaying)) return 1;
    if (std::regex_match(uri, regexListAll)) return 2;
    if (std::regex_match(uri, regexStop)) return 3;
    return -1;
}