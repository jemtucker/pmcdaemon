//
//  audio.h
//  pimediacenter
//
//  Created by Jem Tucker on 04/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pimediacenter__audio__
#define __pimediacenter__audio__

#include <stdio.h>
#include <ao/ao.h>
#include <mpg123.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#include "logging.h"

typedef enum {
    PMC_STATE_PLAYING_URI,
    PMC_STATE_PAUSE,
    PMC_STATE_STOPPED
} pmc_playstate_t;

pmc_playstate_t current_state(void);

bool is_playing(void);
int thread_stream_url(const char *url);
const char *now_playing(void);

#endif /* defined(__pimediacenter__audio__) */
