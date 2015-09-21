//
//  RequestHandler.h
//  pmcdaemon
//
//  Created by Jem Tucker on 05/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__RequestHandler__
#define __pmcdaemon__RequestHandler__

#include <memory>

#include "CivetServer.h"
#include "Device.h"


class RequestHandler : public CivetHandler {
    std::shared_ptr<Device> device;
    
    const std::vector<std::string> routes {
        R"(^\/api\/nowplaying$)",
        R"(^\/api\/listall$)",
        R"(^\/api\/stop$)",
        R"(^\/api\/play.*)"
    };
    
    int matchRequest(std::string uri);
    
    // TODO this should return int
    std::string parseQueryString(std::string queryString);
    
    void listAllStations(struct mg_connection *conn);
    
public:
    RequestHandler(Device *d): device(d) {}
    
    virtual bool handlePost(CivetServer *cs, struct mg_connection *conn) override;
};

#endif /* defined(__pmcdaemon__RequestHandler__) */
