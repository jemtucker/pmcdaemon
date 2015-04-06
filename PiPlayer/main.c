//
//  main.c
//  PiPlayer
//
//  Created by Jem Tucker on 03/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include <stdio.h>
#include "piutil.h"
#include "options.h"
#include "server.h"
#include "streamaudio.h"

// Default configuration
Configuration CONFIGURATION_DEFAULT = {
    "DEBUG", "8080", ""
};


int main(int argc, char *argv[]) {
    Configuration conf = CONFIGURATION_DEFAULT;
    
    // Parse the options
    parse_options(argc, argv, &conf);
    
    // Initialise using configuration
    set_log_level(conf.logging_level);
    set_listening_port(conf.port);
    
    // Stream?
    if (string_non_empty(conf.stream_url)) {
        thread_stream_url(conf.stream_url);
    }
    
    run_server();
    
    return 0;
}



