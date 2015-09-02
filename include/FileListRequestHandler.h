//
//  FileListRequestHandler.h
//  pmcdaemon
//
//  Created by Jem Tucker on 15/08/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__FileListRequestHandler__
#define __pmcdaemon__FileListRequestHandler__

#include "RequestHandler.h"

class FileListRequestHandler: public RequestHandler {
    
    
public:
    FileListRequestHandler(Device *d): RequestHandler(d) {}
    virtual bool handlePost(CivetServer *, struct mg_connection *) override;
};


#endif /* defined(__pmcdaemon__FileListRequestHandler__) */
