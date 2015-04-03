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
#include "logging.h"

void parse_options(int argc, char *argv[]);

void print_usage(void);
void print_help(void);
void print_usage_exit(void);

#endif /* defined(__PiPlayer__options__) */
