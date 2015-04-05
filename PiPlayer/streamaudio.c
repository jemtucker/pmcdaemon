//
//  audio.c
//  PiPlayer
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

bool is_playing = false;

pthread_t thread_current;

// Mutexts
pthread_mutex_t mutex_streaming;

// Functions
void *stream_url(void *raw_url);
int cancel_streaming_safely();
size_t play_stream(void *buffer, size_t size, size_t nmeb, void *userp);

// Implementation
int thread_stream_url(char *url) {
    if (is_playing) {
        dbg("A thread is already streaming, now stopping...");
        int err = pthread_cancel(thread_current);
        if (err) {
            // Thread not cancelled
            errf("Attempt to cancel thread failed with return value: %s", err);
            return err;
        }
        cancel_streaming_safely();
    }
    
    is_playing = true;
    
    dbg("Beggining streaming in new thread");
    pthread_create(&thread_current, NULL, stream_url, url);
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
    
    is_playing = false;
    
    return 0;
}

void *stream_url(void *raw_url) {
    const char *url = (char *)raw_url;
    dbgf("Streaming URL %s", url);
    
    ao_initialize();
    mpg123_init();
    handle_mpg123 = mpg123_new(NULL, NULL);
    mpg123_open_feed(handle_mpg123);
    
    handle_curl = curl_easy_init();
    curl_easy_setopt(handle_curl, CURLOPT_WRITEFUNCTION, play_stream);
    curl_easy_setopt(handle_curl, CURLOPT_URL, url);
    curl_easy_perform(handle_curl);
    
    cancel_streaming_safely();
    
    return 0;
}


size_t play_stream(void *buffer, size_t size, size_t nmeb, void *userp) {
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









