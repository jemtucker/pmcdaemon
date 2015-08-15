//
//  StationIdRequest.h
//  pmcdaemon
//
//  Created by Jem Tucker on 05/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__StationIdRequest__
#define __pmcdaemon__StationIdRequest__

#include <string>

#include "Request.h"
#include "Configuration.h"

class StationIdRequest: public Request {
    Configuration *configuration;
public:
    StationIdRequest(const struct mg_request_info *, Configuration *);
    
    int moduleType() override;
    // TODO make parent class urlrequest with virtual method url()
    std::string url();
};

#endif /* defined(__pmcdaemon__StationIdRequest__) */
