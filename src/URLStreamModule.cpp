//
//  URLStreamModule.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "URLStreamModule.h"

#include "AudioController.h"
#include "Configuration.h"

#define DEFAULT_URL 0

URLStreamModule::URLStreamModule(): ac(new AudioController()) {
    // TODO pass audiocontroller on construction?
    init();
}

URLStreamModule::~URLStreamModule() {
    curl_easy_cleanup(curl);
}

void URLStreamModule::init() {
    ac->init();
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &AudioController::staticPlayStream);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, ac.get());
}

void URLStreamModule::playUrl(std::string &url) {
    stop();
    ac->start();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    playThread.release();
    playThread.reset(new std::thread(&curl_easy_perform, curl));
}

void URLStreamModule::play() {
    playUrl(currentUrl);
}

void URLStreamModule::stop() {
    ac->stop();
    if (playThread != nullptr && playThread->joinable()) {
        playThread->join();
    }
}


