//
//  StationRequestHandler.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 05/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "StationRequestHandler.h"
#include "StationIdRequest.h"

bool StationRequestHandler::handlePost(CivetServer *server, struct mg_connection *conn) {
    pmcserver->queueRequest(new StationIdRequest(pmcplayer, mg_get_request_info(conn)));
    return true;
}



