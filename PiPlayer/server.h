//
//  server.h
//  PiPlayer
//
//  Created by Jem Tucker on 03/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __PiPlayer__server__
#define __PiPlayer__server__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "mongoose.h"
#include "logging.h"
#include "streamaudio.h"

int run_server(void);
int set_listening_port(char* port);

#endif /* defined(__PiPlayer__server__) */
