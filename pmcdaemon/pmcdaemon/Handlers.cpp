//
//  Handlers.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 04/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Handlers.h"
#include <iostream>

#define QUERY_ID "id="

RadioHandler::RadioHandler(Player *player) {
    this->player = player;
}

bool RadioHandler::handlePost(CivetServer *server, struct mg_connection *conn) {
    const struct mg_request_info * req_info = mg_get_request_info(conn);;
    processQuery(req_info->query_string);
    
    mg_printf(conn, "HTTP/1.1 200 OK\r\n");
    
    return true;
}

bool RadioHandler::processQuery(const char *query) {
    std::string string(query);
    std::string idString = string.substr(strlen(QUERY_ID));
    int id = std::stoi(idString);
    std::cout << "Recieved request to play station: "
              << id
              << std::endl;
    player->play(id);
    return true;
}