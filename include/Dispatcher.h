//
//  Dispatcher.h
//  pmcdaemon
//
//  Created by Jem Tucker on 05/08/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Dispatcher__
#define __pmcdaemon__Dispatcher__

#include <map>
#include <mutex>
#include <queue>

#include "Request.h"
#include "Module.h"

class URLStreamModule;

enum ModuleType {
    URL_STREAM     = 1,
    FILE_STREAM    = 2,
    ADMINISTRATION = 3
};

class Dispatcher {
    std::mutex queueMutex;
    // TODO shared_ptr<Request>
    std::queue<Request *> requestQueue;
    std::map<int, std::unique_ptr<Module>> modules;
    bool queueIsEmpty();
    void emptyQueue();
    Request *pop();
    void push(Request *request);
    void dispatch(Request *request);
    
public:
    Dispatcher();
    void queueRequest(Request *request);
};

#endif /* defined(__pmcdaemon__AudioController__) */
