//
//  StationRequestHandler.h
//  pmcdaemon
//
//  Created by Jem Tucker on 05/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__StationRequestHandler__
#define __pmcdaemon__StationRequestHandler__

#include <stdio.h>

#include "RequestHandler.h"

class StationRequestHandler : public RequestHandler {
public:
    StationRequestHandler(Server *s, Player *p): RequestHandler(s, p) {}
    bool handlePost(CivetServer *, struct mg_connection *) override;
};

#endif /* defined(__pmcdaemon__StationRequestHandler__) */
