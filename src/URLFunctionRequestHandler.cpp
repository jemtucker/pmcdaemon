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

#define API_STRING "/api/func/"

#define REGEX_LISTALL "/^\\/api\\/func\\/listall$/"
#define REGEX_NOWPLAYING "/^\\/api\\/func\\/nowplaying$/"
#define REGEX_STOP "/^\\/api\\/func\\/stop$/"

bool URLFunctionRequestHandler::handlePost(CivetServer *s, struct mg_connection *conn) {
    auto *info = mg_get_request_info(conn);
    std::string requestUri = info->uri;
    std::string apiString = API_STRING;
    requestUri.substr(apiString.length());
    
    switch (matchRequest(requestUri)) {
        case 1:
            mg_printf(conn, "HTTP/1.1 200 OK\n\n%s\n", "now playingggggg");
            break;
        case 2:
            mg_printf(conn, "HTTP/1.1 200 OK\n\n%s\n", "list all");
            break;
        case 3:
            mg_printf(conn, "HTTP/1.1 200 OK\n\n%s\n", "Stopping");
            break;
            
        default:
            mg_printf(conn, "HTTP/1.1 404 Not Found\n\nShit on it!\n");
            break;
    }
    
    //mg_printf(conn, "HTTP/1.1 200 OK\n\nRequest Queued\n%s", info->uri);
    
    return true;
}

int URLFunctionRequestHandler::matchRequest(std::string uri) {
    std::regex regexNowPlaying(REGEX_NOWPLAYING); // Make static
    std::regex regexListAll(REGEX_LISTALL);
    std::regex regexStop(REGEX_STOP);
    
    if (std::regex_match(uri, regexNowPlaying)) return 1;
    if (std::regex_match(uri, regexListAll)) return 2;
    if (std::regex_match(uri, regexStop)) return 3;
    return -1;
}