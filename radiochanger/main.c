//
//  main.c
//  radiochanger
//
//  Created by Jem Tucker on 06/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include <stdio.h>
#include <curl/curl.h>
#include <unistd.h>
#include <stdlib.h>

#define DEFAULT_PORT "8080"

// Structures
struct Channel {
    char *name;
    char *url;
};

// Functions
void print_help(void);

int main(int argc, char **argv) {
    char *path_to_config = NULL;
    char *port = DEFAULT_PORT;
    char opt;
    
    // Parse options
    opterr = 0;
    while ((opt = getopt(argc, argv, "c:p:h")) != -1 && (opt != 255)) {
        switch (opt) {
            case 'c':
                path_to_config = optarg;
                break;
            case 'p':
                // Currently unsafe
                port = optarg;
                break;
            case 'h':
                print_help();
                break;
            default:
                print_help();
        }
    }
    
    // Open channels.conf
    
    return 0;
}

int load_channels(char *conf_file, struct Channel *channels[]) {
    FILE *conf;
    conf = fopen(conf_file, "r");
    int r, line = 0;
    char *name, *url;
    
    while ((r = fscanf(conf, "%s %s\n", name, url)) != EOF) {
        
    }
    
    fclose(conf);
    return 0;
}

void print_help(void) {
    printf("Usage: PiPlayer [-lph] \n");
    printf("    -c: <conf>  Path to channels file.\n");
    printf("    -p: port    Pimediacenter server port.\n");
    printf("    -h:         Display this help.\n");
    exit(EXIT_SUCCESS);
}

