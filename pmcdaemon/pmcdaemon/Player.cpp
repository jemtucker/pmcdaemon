//
//  Player.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Player.h"

#define BITS 8
#define DEFAULT_URL 0

Player::Player(Configuration *conf): configuration(conf),
currentUrl(configuration->getUrl(DEFAULT_URL)) {}


/* Playing methods */

void Player::play(std::string *url) {
    while (getStatus() == PLAYING) stop();
    setStatus(PLAYING);
    
    ao_initialize();
    
    mpg123_init();
    mh = mpg123_new(NULL, NULL);
    mpg123_open_feed(mh);
    
    curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Player::static_play_stream);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(curl, CURLOPT_URL, url->c_str());
    
    playThread.reset(new std::thread(&curl_easy_perform, curl));
}

void Player::play(int stationId) {
    play(configuration->getUrl(stationId));
}

void Player::play() {
    play(currentUrl.get());
}

void Player::stop() {
    setStatus(STOPPED);
    playThread->join();
    
    curl_easy_cleanup(curl);
    
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    
    ao_close(ao);
    ao_shutdown();
}


/* Callbacks for curl */

size_t Player::play_stream(void *buffer, size_t size, size_t nmemb, void *userp) {
    if (static_cast<Player *>(userp)->status == STOPPED) return CURL_READFUNC_ABORT;
    
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

size_t Player::static_play_stream(void *buffer, size_t size, size_t nmemb, void *userp) {
     return static_cast<Player *>(userp)->play_stream(buffer, size, nmemb, userp);
}


/* Getters and Setters */

void Player::setStatus(Status status) {
    mutexStatus.lock();
    this->status = status;
    mutexStatus.unlock();
}

Status Player::getStatus(void) {
    mutexStatus.lock();
    Status rtn = status;
    mutexStatus.unlock();
    return rtn;
}



