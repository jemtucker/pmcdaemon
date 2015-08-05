//
//  AudioController.h
//  pmcdaemon
//
//  Created by Jem Tucker on 04/08/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__AudioController__
#define __pmcdaemon__AudioController__

#include <stdio.h>

#include <ao/ao.h>
#include <mpg123.h>
#include <mutex>

enum AudioControllerState {
    PLAYING = 1,
    STOPPED = 2
};

class AudioController {
    std::mutex stateMutex;
    
    mpg123_handle *mh;
    ao_device *ao;
    
    AudioControllerState state = STOPPED;
    
    size_t playStream(void *buffer, size_t size, size_t nmemb, void *userp);
    
    
public:
    ~AudioController();
    
    void init();
    
    AudioControllerState currentState();
    void setCurrentState(AudioControllerState s);
    static size_t staticPlayStream(void *buffer, size_t size, size_t nmemb, void *userp);
};

#endif /* defined(__pmcdaemon__AudioController__) */
