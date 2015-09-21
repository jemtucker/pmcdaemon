//
//  StopPlayingRequest.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 07/09/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "StopPlayingRequest.h"

StopPlayingRequest::StopPlayingRequest(const struct mg_connection *conn): Request(conn) {
    
}

int StopPlayingRequest::moduleType() {
    return 2; // TODO Use Enum
}