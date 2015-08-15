//
//  URLStreamModule.h
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__URLStreamModule__
#define __pmcdaemon__URLStreamModule__

#include <string>
#include <thread>
#include <memory>
#include <curl/curl.h>

#include "Module.h"

class AudioController;

class URLStreamModule: public Module {
    /* Properties */
    std::unique_ptr<std::thread> playThread;
    std::unique_ptr<AudioController> ac;
    std::string currentUrl;
    CURL *curl;
    
    /* Playing methods */
    void playUrl(std::string &);
    void play();
    void stop();
    void init();
    
public:
    URLStreamModule();
    ~URLStreamModule();
    
    virtual void execute(Request *request) override;
};


#endif /* defined(__pmcdaemon__URLStreamModule__) */
