//
//  audio.h
//  PiPlayer
//
//  Created by Jem Tucker on 04/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __PiPlayer__audio__
#define __PiPlayer__audio__

#include <stdio.h>
#include <ao/ao.h>
#include <mpg123.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "logging.h"

bool is_playing(void);
int thread_stream_url(const char *url);

#endif /* defined(__PiPlayer__audio__) */
