//
//  FileListRequestHandler.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 15/08/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "FileListRequestHandler.h"

#include "FileListRequest.h"

bool FileListRequestHandler::handlePost(CivetServer *s, struct mg_connection *conn) {
    Request *request = new FileListRequest(mg_get_request_info(conn));
    device->getDispatcher()->queueRequest(request);
    mg_printf(conn, "HTTP/1.1 200 OK\n\nRequest Queued\n");
    return true;
}