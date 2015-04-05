//
//  main.c
//  PiPlayer
//
//  Created by Jem Tucker on 03/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include <stdio.h>
#include "options.h"
#include "server.h"
#include "streamaudio.h"

// Default configuration
Configuration CONFIGURATION_DEFAULT = {
    "DEBUG", "8080", ""
};


int main(int argc, char * argv[]) {
    Configuration *conf = &CONFIGURATION_DEFAULT;
    
    // Parse the options.
    parse_options(argc, argv, conf);
    
    stream_url(STREAM_URL);
//    run_server();
    
    return 0;
}



