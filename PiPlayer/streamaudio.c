//
//  audio.c
//  PiPlayer
//
//  Created by Jem Tucker on 04/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "streamaudio.h"

#define STREAM_URL "http://bbcmedia.ic.llnwd.net/stream/bbcmedia_radio3_mf_p"
#define BITS_IN_BYTE 8

// Forward declarations
// Variables
mpg123_handle *mpg_handle = NULL;
ao_device *device = NULL;
CURL *curl_handle = NULL;

// Functions
size_t play_stream(void *buffer, size_t size, size_t nmeb, void *userp);

int stream_test(void) {
    ao_initialize();
    mpg123_init();
    mpg_handle = mpg123_new(NULL, NULL);
    mpg123_open_feed(mpg_handle);
    
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, play_stream);
    curl_easy_setopt(curl_handle, CURLOPT_URL, STREAM_URL);
    curl_easy_perform(curl_handle);
    curl_easy_cleanup(curl_handle);
    
    mpg123_close(mpg_handle);
    mpg123_delete(mpg_handle);
    mpg123_exit();
    
    ao_close(device);
    ao_shutdown();
    
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
    
    mpg123_feed(mpg_handle, buffer, size * nmeb);
    
    // Stream loop;
    do {
        err = mpg123_decode_frame(mpg_handle, &frame_offset, &audio, &done);
        switch (err) {
            case MPG123_NEW_FORMAT:
                mpg123_getformat(mpg_handle, &rate, &chanels, &encoding);
                format.bits = mpg123_encsize(encoding) * BITS_IN_BYTE;
                format.rate = rate;
                format.channels = chanels;
                format.byte_format = AO_FMT_NATIVE;
                format.matrix = 0;
                device = ao_open_live(ao_default_driver_id(), &format, NULL);
                break;
            case MPG123_OK:
                ao_play(device, audio, done);
                break;
            case MPG123_NEED_MORE:
                break;
            default:
                break;
        }
    } while (done > 0);
    
    return size * nmeb;
}









