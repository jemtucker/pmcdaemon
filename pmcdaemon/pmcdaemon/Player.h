//
//  Player.h
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Player__
#define __pmcdaemon__Player__

#include <stdio.h>
#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <memory>
#include <mpg123.h>
#include <ao/ao.h>
#include <curl/curl.h>

#include "Configuration.h"

enum Status {PLAYING, STOPPED};

class Player {
    /* Mutexes */
    std::mutex mutexStatus;
    
    /* Properties */
    std::unique_ptr<Configuration> configuration;
    std::unique_ptr<std::string> currentUrl;
    std::unique_ptr<std::thread> playThread;
    
    Status status = STOPPED;
    
    /* Internals */
    mpg123_handle *mh;
    ao_device *ao;
    CURL *curl;
    
    
    /* Callbacks for curl */
    size_t play_stream(void *, size_t, size_t, void *);
    static size_t static_play_stream(void *, size_t, size_t, void *);
    
    /* Private setters */
    void setStatus(Status);
    
public:
    Player(Configuration *);
    
    /* Playing methods */
    void play(std::string *);
    void play(int);
    void play();
    void stop();
    
    /* Getters and setters */
    Status getStatus();
};


#endif /* defined(__pmcdaemon__Player__) */
