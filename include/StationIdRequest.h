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
    StationIdRequest(const struct mg_request_info *);
    void execute(Device *) override;
};

#endif /* defined(__pmcdaemon__StationIdRequest__) */
