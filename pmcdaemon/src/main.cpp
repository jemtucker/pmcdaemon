//
//  main.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//


#include <unistd.h>

#include "Device.h"
#include "Session.h"

int main(int argc, const char * argv[]) {
    new Device();
//    new Session("", "");
    usleep(30000 * 1000);
    
    return 0;
}