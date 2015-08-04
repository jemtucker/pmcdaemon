//
//  main.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//


#include <unistd.h>

#include "Device.h"

int main(int argc, const char * argv[]) {
    Device *device = new Device();
    device->init();
    return 0;
}