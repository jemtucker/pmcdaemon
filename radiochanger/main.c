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
#include <string.h>

#define RC_DEFAULT_PORT "8080"
#define RC_MAX_CHANNELS 10

// Structures
struct Channel {
    char *name;
    char *url;
};

// Functions
void print_help(void);
struct Channel *load_channels(char *conf_filechannels);

int main(int argc, char **argv) {
    char *path_to_config = NULL;
    char *port = RC_DEFAULT_PORT;
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
    
    struct Channel *channels = load_channels(path_to_config);
    int channels_length = (int) channels - 1;
    for (int i = 0; i < channels_length; i ++) {
        printf("Name: %s URL: %s\n", channels[i].name, channels[i].url);
    }
    // Open channels.conf
    
    return 0;
}

struct Channel *load_channels(char *conf_file) {
    // Make memory allocation dynamic with no max channels
    struct Channel *channels = malloc(sizeof(struct Channel *) * RC_MAX_CHANNELS);
    
    struct Channel *t_channel;
    FILE *conf;
    conf = fopen(conf_file, "r");
    int r, i = 0;
    
    // Errors if input string is longer than buffers
    char name[10], url[100];
    while ((r = fscanf(conf, "%s %s\n", name, url)) != EOF || i > RC_MAX_CHANNELS) {
        t_channel = malloc(sizeof(struct Channel));
        
        t_channel->url = malloc(strlen(url) * sizeof(char));
        t_channel->name = malloc(strlen(name) * sizeof(char));
        
        strcpy(t_channel->url, url);
        strcpy(t_channel->name, name);
        
        channels[i] = *t_channel;
        i ++;
    }
    fclose(conf);
    return channels;
}

void print_help(void) {
    printf("Usage: PiPlayer [-lph] \n");
    printf("    -c: <conf>  Path to channels file.\n");
    printf("    -p: port    Pimediacenter server port.\n");
    printf("    -h:         Display this help.\n");
    exit(EXIT_SUCCESS);
}

