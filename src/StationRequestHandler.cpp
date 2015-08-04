//
//  StationRequestHandler.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 05/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "StationRequestHandler.h"

#include "StationIdRequest.h"

bool StationRequestHandler::handlePost(CivetServer *cs, struct mg_connection *conn) {
    device->queueRequest(new StationIdRequest(mg_get_request_info(conn)));
    mg_printf(conn, "HTTP/1.1 200 OK\n\nRequest Queued\n");
    return true;
}



