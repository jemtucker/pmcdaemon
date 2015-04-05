//
//  piutil.h
//  PiPlayer
//
//  Utilities for the PiPlayer project
//
//  Created by Jem Tucker on 03/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __PiPlayer__piutil__
#define __PiPlayer__piutil__

#include <stdio.h>
#include <stdlib.h>
#include "logging.h"

int copystring(const char *in, char *out);
const char *uppercase_string(const char *string);
int string_non_empty(const char *string);

#endif /* defined(__PiPlayer__piutil__) */
