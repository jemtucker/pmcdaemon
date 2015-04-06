//
//  audio.c
//  pimediacenter
//
//  Created by Jem Tucker on 04/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "streamaudio.h"

#define BITS_IN_BYTE 8

// Forward declarations

mpg123_handle *handle_mpg123 = NULL;
ao_device *handle_aodevice = NULL;
CURL *handle_curl = NULL;

bool mutex_init = false;
bool _is_playing = false;
bool _is_init = false;

pthread_t thread_current;

// Mutex
pthread_mutex_t is_playing_mutex;
pthread_mutex_t is_init_mutex;

// Functions
void *stream_url(void *raw_url);
int cancel_streaming_safely();
size_t play_stream(void *buffer, size_t size, size_t nmeb, void *userp);
void init(void);

bool is_playing(void);
void set_playing(bool boolean);
bool is_init(void);
void set_init(bool boolean);

// Implementation
int thread_stream_url(const char *url) {
    if (is_playing()) {
        dbg("A thread is already streaming, now stopping...");
        
        // Stop then sleep to allow curl to pause and shutdown
        // TODO horrible mem leak
        set_playing(false);
        
        while (is_init()) {
            usleep(100);
        }
        
        int err = pthread_cancel(thread_current);
        
        if (err) {
            // Thread not cancelled
            errf("Attempt to cancel thread failed with return value: %s", err);
            return err;
        }
    }
    
    set_playing(true);
    
    // Mem leak and why + 1???
    char *stored_url = malloc(strlen(url) + 1);
    
    strcpy(stored_url, url);
    
    dbg("Beggining streaming in new thread");
    pthread_create(&thread_current, NULL, stream_url, stored_url);
    dbg("Streaming started succesfully");
    
    return 0;
}

int cancel_streaming_safely() {
    // TODO Mutext here
    
    curl_easy_cleanup(handle_curl);
    
    mpg123_close(handle_mpg123);
    mpg123_delete(handle_mpg123);
    mpg123_exit();
    
    ao_close(handle_aodevice);
    ao_shutdown();
    
    set_playing(false);
    set_init(false);
    
    return 0;
}

void *stream_url(void *raw_url) {
    const char *url = (const char *)raw_url;
    dbgf("Streaming URL %s", url);
    
    if (!is_init()) init();
    
    curl_easy_reset(handle_curl);
    curl_easy_setopt(handle_curl, CURLOPT_URL, url);
    curl_easy_setopt(handle_curl, CURLOPT_WRITEFUNCTION, play_stream);
    curl_easy_perform(handle_curl);
    
    free(raw_url);
    cancel_streaming_safely();
    return 0;
}

void init(void) {
    if (!mutex_init) {
        pthread_mutex_init(&is_playing_mutex, NULL);
        pthread_mutex_init(&is_init_mutex, NULL);
        mutex_init = true;
    }
    ao_initialize();
    mpg123_init();
    handle_mpg123 = mpg123_new(NULL, NULL);
    mpg123_open_feed(handle_mpg123);
    handle_curl = curl_easy_init();
    set_init(true);
}


size_t play_stream(void *buffer, size_t size, size_t nmeb, void *userp) {
    if (!is_playing()) return CURLE_ABORTED_BY_CALLBACK;
    
    int err;
    off_t frame_offset;
    unsigned char *audio;
    size_t done; // Number of bytes decoded
    ao_sample_format format;
    int chanels, encoding;
    long rate;
    
    mpg123_feed(handle_mpg123, buffer, size * nmeb);
    
    // Stream loop;
    do {
        err = mpg123_decode_frame(handle_mpg123, &frame_offset, &audio, &done);
        switch (err) {
            case MPG123_NEW_FORMAT:
                mpg123_getformat(handle_mpg123, &rate, &chanels, &encoding);
                format.bits = mpg123_encsize(encoding) * BITS_IN_BYTE;
                format.rate = rate;
                format.channels = chanels;
                format.byte_format = AO_FMT_NATIVE;
                format.matrix = 0;
                handle_aodevice = ao_open_live(ao_default_driver_id(), &format, NULL);
                break;
            case MPG123_OK:
                ao_play(handle_aodevice, audio, done);
                break;
            case MPG123_NEED_MORE:
                break;
            default:
                break;
        }
    } while (done > 0);
    
    return size * nmeb;
}

bool is_playing(void) {
    pthread_mutex_lock(&is_playing_mutex);
    bool retval = _is_playing;
    pthread_mutex_unlock(&is_playing_mutex);
    return retval;
}

void set_playing(bool boolean) {
    pthread_mutex_lock(&is_playing_mutex);
    _is_playing = boolean;
    pthread_mutex_unlock(&is_playing_mutex);
}

bool is_init(void) {
    pthread_mutex_lock(&is_init_mutex);
    bool retval = _is_init;
    pthread_mutex_unlock(&is_init_mutex);
    return retval;
}

void set_init(bool boolean) {
    pthread_mutex_lock(&is_init_mutex);
    _is_init = boolean;
    pthread_mutex_unlock(&is_init_mutex);
}









