//
//  URLFunctionRequest.h
//  pmcdaemon
//
//  Created by Jem Tucker on 07/09/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__UrlFunctionRequest__
#define __pmcdaemon__UrlFunctionRequest__

#include "Request.h"

class URLFunctionRequest : public Request {
public:
    virtual int moduleType() override;
    
};

#endif /* defined(__pmcdaemon__URLFunctionRequest__) */
