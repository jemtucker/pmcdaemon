//
//  options.h
//  PiPlayer
//
//  Created by Jem Tucker on 03/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __PiPlayer__options__
#define __PiPlayer__options__

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct configuration {
    char *logging_level;
    char *port;
    char *stream_url;
} Configuration;

void parse_options(int argc, char *argv[], Configuration *conf) ;

#endif /* defined(__PiPlayer__options__) */
