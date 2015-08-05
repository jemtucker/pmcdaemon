//
//  RadioModule.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "RadioModule.h"

#define BITS 8
#define DEFAULT_URL 0

RadioModule::RadioModule(std::shared_ptr<Configuration> conf): Module(conf), currentUrl(*configuration->getUrl(DEFAULT_URL)) { }

void RadioModule::init() {
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &RadioModule::static_play_stream);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
    
    // TODO move out into audiocontroller
    ao_initialize();
    mpg123_init();
    mh = mpg123_new(NULL, NULL);
}

RadioModule::~RadioModule() {
    curl_easy_cleanup(curl);
    
    // TODO move out
    mpg123_delete(mh);
    mpg123_exit();
    ao_close(ao);
    ao_shutdown();
}


/* Playing methods */
void RadioModule::playUrl(std::string &url) {
    while (getStatus() == PLAYING) stop();
    setStatus(PLAYING);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    mpg123_open_feed(mh);
    playThread.release();
    playThread.reset(new std::thread(&curl_easy_perform, curl));
}

void RadioModule::play(std::string &stationId) {
    try {
        int id = std::stoi(stationId);
        std::string url = *configuration->getUrl(id);
        playUrl(url);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void RadioModule::play() {
    play(currentUrl);
}

void RadioModule::stop() {
    setStatus(STOPPED);
    playThread->join();
    mpg123_close(mh);
}


/* Callbacks for curl */

size_t RadioModule::play_stream(void *buffer, size_t size, size_t nmemb, void *userp) {
    if (static_cast<RadioModule *>(userp)->status == STOPPED)
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
                format.bits = mpg123_encsize(encoding) * BITS;
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

size_t RadioModule::static_play_stream(void *buffer, size_t size, size_t nmemb, void *userp) {
     return static_cast<RadioModule *>(userp)->play_stream(buffer, size, nmemb, userp);
}

void RadioModule::setStatus(Status status) {
    std::lock_guard<std::mutex> lock(mutexStatus);
    this->status = status;
}

Status RadioModule::getStatus(void) {
    std::lock_guard<std::mutex> lock(mutexStatus);
    return status;
}



