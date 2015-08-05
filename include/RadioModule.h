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
#include <curl/curl.h>

#include "Module.h"

class AudioController;

class RadioModule: public Module {
    /* Properties */
    std::unique_ptr<std::thread> playThread;
    std::unique_ptr<AudioController> ac;
    
    std::string currentUrl;
    
    /* Internals */
    CURL *curl;
    
public:
    RadioModule(std::shared_ptr<Configuration>);
    ~RadioModule();
    
    void init() override;
    
    /* Playing methods */
    void playUrl(std::string &);
    void play(std::string &) override;
    void play();
    void stop();
};


#endif /* defined(__pmcdaemon__RadioModule__) */
