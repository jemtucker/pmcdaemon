//
//  logging.h
//  PiPlayer
//
//  Created by Jem Tucker on 03/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __PiPlayer__logging__
#define __PiPlayer__logging__

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "piutil.h"

typedef enum {LEVEL_ERROR, LEVEL_INFO, LEVEL_DEBUG} logging_level_t;

// Perform logging
void logmsgf(logging_level_t lvl, char format[], ...);
void logmsg(char message[], logging_level_t lvl);
void info(char message[]);
void err(char message[]);
void dbg(char message[]);

// Configure logging
void set_log_level(logging_level_t lvl);

// Util methods
void log_message(char message[], char level[]);
void get_log_time(char out[]);
void level_to_string(logging_level_t lvl, char out[]);

#endif /* defined(__PiPlayer__logging__) */
