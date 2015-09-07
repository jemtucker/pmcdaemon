//
//  URLFunctionModule.h
//  pmcdaemon
//
//  Created by Jem Tucker on 07/09/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__URLFunctionModule__
#define __pmcdaemon__URLFunctionModule__

#include "Module.h"

class URLFunctionModule : public Module {
public:
    virtual void execute(Request *r) override;
};

#endif /* defined(__pmcdaemon__URLFunctionModule__) */
