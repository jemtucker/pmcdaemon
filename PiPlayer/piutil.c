//
//  piutil.c
//  PiPlayer
//
//  Utilities for the PiPlayer project
//
//  Created by Jem Tucker on 03/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "piutil.h"
#include "logging.h"


int copystring(const char *in, char *out) {
    int in_size = sizeof(in);
    int out_size = sizeof(out);
    
    if (in_size > out_size) {
        dbg("Copy string failed, input larger than output.");
        return -1;
    }
    
    for (int i = 0; i < in_size; i++) {
        out[i] = in[i];
    }
    
    return 0;
}