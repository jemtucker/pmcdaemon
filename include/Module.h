//
//  Module.h
//  pmcdaemon
//
//  Created by Jem Tucker on 17/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Module__
#define __pmcdaemon__Module__

class Request;

class Module {
public:
    virtual void execute(Request *request) = 0;
};

#endif /* defined(__pmcdaemon__Module__) */
