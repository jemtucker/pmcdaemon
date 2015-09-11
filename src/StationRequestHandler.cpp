//
//  StationRequestHandler.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 05/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "StationRequestHandler.h"

#include "Dispatcher.h"
#include "StationIdRequest.h"

bool StationRequestHandler::handlePost(CivetServer *cs, struct mg_connection *conn) {
    Request *request = new StationIdRequest(conn, device->getConfig());
    device->getDispatcher()->dispatch(request);
    return true;
}



