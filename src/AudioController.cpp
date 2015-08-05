//
//  AudioController.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 04/08/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "AudioController.h"

#include <curl/curl.h>

AudioController::~AudioController() {
    mpg123_delete(mh);
    mpg123_exit();
    ao_close(ao);
    ao_shutdown();
}

void AudioController::init() {
    ao_initialize();
    mpg123_init();
    mh = mpg123_new(NULL, NULL);
}

size_t AudioController::playStream(void *buffer, size_t size, size_t nmemb, void *userp) {
    if (static_cast<AudioController *>(userp)->currentState() == STOPPED)
        return CURL_READFUNC_ABORT;
    
    int err;
    off_t frame_offset;
    unsigned char *audio;
    size_t done;
    ao_sample_format format;
    int channels, encoding;
    long rate;
    
    mpg123_feed(mh, (const unsigned char*) buffer, size * nmemb);
    do {
        err = mpg123_decode_frame(mh, &frame_offset, &audio, &done);
        switch(err) {
            case MPG123_NEW_FORMAT:
                mpg123_getformat(mh, &rate, &channels, &encoding);
                format.bits = mpg123_encsize(encoding) * 8;  // Bits to encode
                format.rate = (int) rate;
                format.channels = channels;
                format.byte_format = AO_FMT_NATIVE;
                format.matrix = 0;
                ao = ao_open_live(ao_default_driver_id(), &format, NULL);
                break;
            case MPG123_OK:
                ao_play(ao, (char *) audio, (uint_32) done);
                break;
            case MPG123_NEED_MORE:
                break;
            default:
                break;
        }
    } while(done > 0);
    
    return size * nmemb;
}

size_t AudioController::staticPlayStream(void *buffer, size_t size, size_t nmemb, void *userp) {
    return static_cast<AudioController*>(userp)->playStream(buffer, size, nmemb, userp);
}

void AudioController::setCurrentState(AudioControllerState s) {
    std::lock_guard<std::mutex> lock(stateMutex);
    state = s;
}

AudioControllerState AudioController::currentState() {
    std::lock_guard<std::mutex> lock(stateMutex);
    return state;
}

