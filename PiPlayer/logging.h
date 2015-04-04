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
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "piutil.h"

typedef enum {LEVEL_ERROR, LEVEL_INFO, LEVEL_DEBUG} logging_level_t;

// Perform logging
void info(const char *message);
void err(const char *message);
void dbg(const char *message);

void infof(const char *format, ...);
void errf(const char *format, ...);
void dbgf(const char *format, ...);

// Configure logging
void set_log_level(const char *level);

#endif /* defined(__PiPlayer__logging__) */
