//
//  StationIdRequest.h
//  pmcdaemon
//
//  Created by Jem Tucker on 05/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__StationIdRequest__
#define __pmcdaemon__StationIdRequest__

#include <stdio.h>

#include "Request.h"

class StationIdRequest: private Request {
public:
    StationIdRequest(const struct mg_request_info *i): Request(i) {}
    void execute() override;
};

#endif /* defined(__pmcdaemon__StationIdRequest__) */
