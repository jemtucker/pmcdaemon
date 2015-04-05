//
//  options.c
//  PiPlayer
//
//  Created by Jem Tucker on 03/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "options.h"

void print_usage(void);
void print_help(void);
void print_usage_exit(void);

extern char *optarg;
extern int opterr;

void parse_options(int argc, char *argv[], struct configuration *conf) {
    char opt;
    opterr = 0;
    while ((opt = getopt(argc, argv, "l:p:u:")) != -1 && (opt != 255)) {
        switch (opt) {
            case 'l': conf->logging_level = optarg; break;
            case 'p': conf->port = optarg; break;
            case 'u': conf->stream_url = optarg; break;
            case 'h': print_help(); break;
            default: print_usage_exit();
        }
    }
}

void print_usage(void) {
    printf("Usage: PiPlayer [-lph] \n");
    printf("    -l: level       Logging level info.\n");
    printf("    -u: url         Stream url.\n");
    printf("    -p: port        REST server port.\n");
    printf("    -h:             Display this help.\n");
}

void print_help(void) {
    print_usage();
    exit(EXIT_SUCCESS);
}

void print_usage_exit(void) {
    print_usage();
    exit(EXIT_FAILURE);
}
