//
//  RadioModule.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "RadioModule.h"

#include "AudioController.h"

#define BITS 8
#define DEFAULT_URL 0

RadioModule::RadioModule(std::shared_ptr<Configuration> conf): Module(conf), currentUrl(*configuration->getUrl(DEFAULT_URL)), ac(new AudioController()) {
    ac->init();
}

void RadioModule::init() {
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &AudioController::staticPlayStream);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, ac.get());
}

RadioModule::~RadioModule() {
    curl_easy_cleanup(curl);
}


/* Playing methods */
void RadioModule::playUrl(std::string &url) {
    stop();
    ac->start();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
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
    ac->stop();
    if (playThread != nullptr) playThread->join();
}


