//
//  main.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <memory>

#include "Configuration.h"
#include "Player.h"
#include "Server.h"

int main(int argc, const char * argv[]) {
    std::string path = "/Users/Jem/workspace/PiPlayer/pmcdaemon/pmcdaemon/stations.conf";
    
    Player *player = new Player(new Configuration(&path));
    
    new Server(player);
    
    while (true) {}
    
    player->play();
    
    usleep(30000 * 1000);
    
    
    std::string test = "http://bbcmedia.ic.llnwd.net/stream/bbcmedia_radio3_mf_p";
    player->play(test);
    
    usleep(30000 * 1000);
    
    return 0;
}