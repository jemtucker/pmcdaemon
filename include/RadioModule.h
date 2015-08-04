//
//  RadioModule.h
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__RadioModule__
#define __pmcdaemon__RadioModule__

#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <memory>
#include <mpg123.h>
#include <ao/ao.h>
#include <curl/curl.h>

#include "Module.h"

enum Status {PLAYING, STOPPED};

class RadioModule: public Module {
    /* Mutexes */
    std::mutex mutexStatus;
    
    /* Properties */
    std::unique_ptr<std::thread> playThread;
    
    std::string currentUrl;
    
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
    RadioModule(std::shared_ptr<Configuration>);
    ~RadioModule();
    
    void init() override;
    
    /* Playing methods */
    void playUrl(std::string &);
    void play(std::string &) override;
    void play();
    void stop();
    
    /* Getters and setters */
    Status getStatus();
};


#endif /* defined(__pmcdaemon__RadioModule__) */
