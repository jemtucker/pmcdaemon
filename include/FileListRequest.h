//
//  FileListRequest.h
//  pmcdaemon
//
//  Created by Jem Tucker on 17/08/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__FileListRequest__
#define __pmcdaemon__FileListRequest__

#include <string>

#include "Request.h"

class FileListRequest: public Request {
    std::string path;
    
public:
    FileListRequest(const struct mg_request_info *i): Request(i) {}
    
    int moduleType() override;
    
    std::string pathToList();
};

#endif /* defined(__pmcdaemon__FileListRequest__) */
