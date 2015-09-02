//
//  FileListRequest.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 17/08/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "FileListRequest.h"

#include "Dispatcher.h"

int FileListRequest::moduleType() {
    return FILE_STREAM;
}