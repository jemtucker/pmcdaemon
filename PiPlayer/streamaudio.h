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
#include "logging.h"

bool is_playing;
int thread_stream_url(char *url);

#endif /* defined(__PiPlayer__audio__) */
