//
//  Session.h
//  pmcdaemon
//
//  Created by Jem Tucker on 18/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Session__
#define __pmcdaemon__Session__

#include <libspotify/api.h>
#include <string>
#include <mutex>

#include "appkey.h"

// Work out how to remove global vars
static int notify_events;
static std::mutex notifyMutex;
static std::condition_variable notify_cond;

class Session {
    sp_session *session;
    sp_session_config config;
    sp_session_callbacks callbacks;
    
    void initSession(std::string, std::string);
    
    std::string readUser();     // Temporary
    std::string readPassword(); // Temporary

public:
    Session(std::string, std::string);
    
    /* Callbacks */
    static void connectionError(sp_session *, sp_error);
    static void loggedIn(sp_session *, sp_error);
    static void loggedOut(sp_session *);
    static void logMessage(sp_session *, const char *);
    static void notifyMainThread(sp_session *);
};

#endif /* defined(__pmcdaemon__Session__) */
