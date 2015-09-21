//
//  StopPlayingRequest.h
//  pmcdaemon
//
//  Created by Jem Tucker on 07/09/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__StopPlayingRequest__
#define __pmcdaemon__StopPlayingRequest__

#include "Request.h"

class StopPlayingRequest : public Request {
public:
    StopPlayingRequest(const struct mg_connection *conn);
    virtual int moduleType() override;
    
};

#endif /* defined(__pmcdaemon__StopPlayingRequest__) */
