//
//  logging.c
//  PiPlayer
//
//  Created by Jem Tucker on 03/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "logging.h"

#define TIME_LENGTH 20

logging_level_t MAX_LEVEL_TO_LOG = LEVEL_DEBUG;

void logmsg(char message[], logging_level_t lvl) {
    if (MAX_LEVEL_TO_LOG >= lvl) {
        switch (lvl) {
            case LEVEL_INFO: info(message); break;
            case LEVEL_ERROR: err(message); break;
            case LEVEL_DEBUG: dbg(message); break;
            default: break;
        }
    }
}

void logmsgf(logging_level_t lvl, char format[], ...) {
    char message[1024];
    va_list args;
    va_start(args, format);
    vsprintf(message, format, args);
    va_end(args);
    logmsg(message, lvl);
}

void info(char message[]) {
    log_message(message, "INFO ");
}

void err(char message[]) {
    log_message(message, "ERROR");
}

void dbg(char message[]) {
    log_message(message, "DEBUG");
}

void set_log_level(const logging_level_t lvl) {
    MAX_LEVEL_TO_LOG = lvl;
    char level[5];
    level_to_string(lvl, level);
    
    char message[31];
    sprintf(message, "Setting logging level to %s", level);
    logmsg(message, LEVEL_DEBUG);
}

void log_message(char message[], char level[]) {
    char t[TIME_LENGTH];
    get_log_time(t);
    printf("%s [%s] %s \n", level, t, message);
}

void get_log_time(char out[]) {
    time_t rawTime;
    time(&rawTime);
    char * time = ctime(&rawTime);
    for (int i = 4; i < 19; i++) {
        out[i - 4] = time[i];
    }
}

void level_to_string(logging_level_t lvl, char out[]) {
    switch (lvl) {
        case LEVEL_INFO: copystring("INFO", out); break;
        case LEVEL_ERROR: copystring("ERROR", out); break;
        case LEVEL_DEBUG: copystring("DEBUG", out); break;
    }
}

