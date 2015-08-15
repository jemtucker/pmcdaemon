//
//  FileListRequestHandler.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 15/08/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "FileListRequestHandler.h"

#include "RequestHandler.h"

class FileListRequestHandler: public RequestHandler {
    
    
public:
    FileListRequestHandler(Device *d): RequestHandler(d) {}
    
};