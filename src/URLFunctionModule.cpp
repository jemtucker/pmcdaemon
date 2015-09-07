//
//  URLFunctionModule.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 07/09/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "URLFunctionModule.h"

#include "URLFunctionRequest.h"

void URLFunctionModule::execute(Request *r) {
    auto request = static_cast<URLFunctionRequest *>(r);
}