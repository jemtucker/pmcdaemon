//
//  StationIdRequest.h
//  pmcdaemon
//
//  Created by Jem Tucker on 05/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__StationIdRequest__
#define __pmcdaemon__StationIdRequest__

#include "Request.h"

class StationIdRequest: public Request {
public:
    StationIdRequest(Player *p, const struct mg_request_info *i): Request(p, i) {}
    void execute() override;
};

#endif /* defined(__pmcdaemon__StationIdRequest__) */
