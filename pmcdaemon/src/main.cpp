//
//  main.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <memory>

#include "Device.h"

int main(int argc, const char * argv[]) {
    new Device();
    
    usleep(30000 * 1000);
    
    return 0;
}