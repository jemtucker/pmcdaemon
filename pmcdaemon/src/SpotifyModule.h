//
//  SpotifyModule.h
//  pmcdaemon
//
//  Created by Jem Tucker on 18/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__SpotifyModule__
#define __pmcdaemon__SpotifyModule__

//#include <libspotify/api.h>
#include <memory>

#include "Module.h"

class Configuration;

class SpotifyModule: public Module {
public:
    SpotifyModule(std::shared_ptr<Configuration>);
    
    void play(std::string &) override;
    void stop() override;
};

#endif /* defined(__pmcdaemon__SpotifyModule__) */
