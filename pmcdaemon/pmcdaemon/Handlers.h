//
//  Handlers.h
//  pmcdaemon
//
//  Created by Jem Tucker on 04/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Handlers__
#define __pmcdaemon__Handlers__

#include <stdio.h>

#include "CivetServer.h"
#include "Player.h"

class RadioHandler : public CivetHandler {
    Player *player;
    bool processQuery(const char *);
    
public:
    RadioHandler(Player *);
    bool handlePost(CivetServer *, struct mg_connection *);
};

#endif /* defined(__pmcdaemon__Handlers__) */
