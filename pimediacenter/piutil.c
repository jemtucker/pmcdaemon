//
//  piutil.c
//  pimediacenter
//
//  Created by Jem Tucker on 03/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "piutil.h"

int copystring(const char *in, char *out) {
    // TODO add sizeof(char)
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

int cat_string(char *buffer, const char *first, const char *other) {
    int buffer_size = sizeof(buffer);
    int first_size = sizeof(first);
    int other_size = sizeof(other);
    
    if (buffer_size < (other_size + first_size)) {
        dbg("Copy string failed, input larger than output.");
        return -1;
    }
    
    int i = 0;
    bool start_adding = false;
     // TODO implement logic
    
    return 0;
}

const char *uppercase_string(const char *string) {
    char *uppercase_string = malloc(sizeof(string));
    copystring(string, uppercase_string);
    for (int i = 0; i < sizeof(uppercase_string); i++) {
        uppercase_string[i] = toupper(uppercase_string[i]);
    }
    return uppercase_string;
}

int string_non_empty(const char *string) {
    if (strcmp("", string) != 0) return 1;
    else return 0;
}