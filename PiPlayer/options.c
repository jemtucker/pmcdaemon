//
//  options.c
//  PiPlayer
//
//  Created by Jem Tucker on 03/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "options.h"

void parse_options(int argc, char *argv[]) {
    char opt;
    
    while ((opt = getopt(argc, argv, "ideh")) != -1) {
        switch (opt) {
            case 'i': set_log_level(LEVEL_INFO); break;
            case 'd': set_log_level(LEVEL_DEBUG); break;
            case 'e': set_log_level(LEVEL_ERROR); break;
            case 'h': print_help(); break;
            default: print_usage_exit();
        }
    }
}

void print_usage(void) {
    printf("Usage: PiPlayer [-ideh] \n");
    printf("        -i: Logging level info.\n");
    printf("        -d: Logging level debug.\n");
    printf("        -e: Logging level error.\n");
    printf("        -h: Display this help.\n");
}

void print_help(void) {
    print_usage();
    exit(EXIT_SUCCESS);
}

void print_usage_exit(void) {
    print_usage();
    exit(EXIT_FAILURE);
}
