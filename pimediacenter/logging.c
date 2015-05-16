//
//  logging.c
//  pimediacenter
//
//  Created by Jem Tucker on 03/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "logging.h"

#define TIME_LENGTH 16

// Maximum level to log to, all levels below are ignored.
// Default to lowest.
logging_level_t MAX_LEVEL_TO_LOG = LEVEL_DEBUG;

// Method declarations
void logmsg(const char *message, logging_level_t lvl);
void log_message(const char *message, const char *level);
void get_log_time(char out[]);
void level_to_string(logging_level_t lvl, char *out);
logging_level_t string_to_level(const char *level);

// Implementation
void logmsg(const char *message, logging_level_t lvl) {
    if (MAX_LEVEL_TO_LOG >= lvl) {
        switch (lvl) {
            case LEVEL_INFO: log_message(message, "INFO "); break;
            case LEVEL_ERROR: log_message(message, "ERROR"); break;
            case LEVEL_DEBUG: log_message(message, "DEBUG"); break;
            default: break;
        }
    }
}

void info(const char *message) {
    logmsg(message, LEVEL_INFO);
}

void err(const char *message) {
    logmsg(message, LEVEL_ERROR);
}

void dbg(const char *message) {
    logmsg(message, LEVEL_DEBUG);
}

void dbgf(const char *format, ...) {
    char message[1024];
    va_list args;
    va_start(args, format);
    vsprintf(message, format, args);
    va_end(args);
    logmsg(message, LEVEL_DEBUG);
}

void errf(const char *format, ...) {
    char message[1024];
    va_list args;
    va_start(args, format);
    vsprintf(message, format, args);
    va_end(args);
    logmsg(message, LEVEL_ERROR);
}

void infof(const char *format, ...) {
    char message[1024];
    va_list args;
    va_start(args, format);
    vsprintf(message, format, args);
    va_end(args);
    logmsg(message, LEVEL_INFO);
}

void set_log_level(const char *level) {
    MAX_LEVEL_TO_LOG = string_to_level(level);
    const char * uppercase_level = uppercase_string(level);
    dbgf("Setting MAX_LEVEL_TO_LOG to %s.", uppercase_level);
    free((void *) uppercase_level);
}

void log_message(const char *message, const char *level) {
    char t[TIME_LENGTH];
    get_log_time(t);
    printf("%s [%s] %s \n", level, t, message);
}

void get_log_time(char *out) {
    time_t raw_time;
    time(&raw_time);
    char * time = ctime(&raw_time);
    for (int i = 4; i < 19; i++) {
        out[i - 4] = time[i];
    }
    out[TIME_LENGTH - 1] = 0;
}

void level_to_string(logging_level_t lvl, char *out) {
    switch (lvl) {
        case LEVEL_INFO: copystring("INFO", out); break;
        case LEVEL_ERROR: copystring("ERROR", out); break;
        case LEVEL_DEBUG: copystring("DEBUG", out); break;
        default: errf("Invalid logging level %d", lvl);
    }
}

logging_level_t string_to_level(const char *level) {
    const char *uppercase_level = uppercase_string(level);
    int retval;
    if (strcmp(uppercase_level, "INFO") == 0) retval = LEVEL_INFO;
    else if (strcmp(uppercase_level, "DEBUG") == 0) retval = LEVEL_DEBUG;
    else if (strcmp(uppercase_level, "ERROR") == 0) retval = LEVEL_ERROR;
    else {
        errf("Logging level %s could not be recognised.", level);
       retval = -1;
    }
    free((void *) uppercase_level);
    return retval;
}

