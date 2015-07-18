//
//  Session.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 18/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Session.h"

#include <iostream>
#include <termios.h>
#include <unistd.h>

#define USER_AGENT "pmcdaemon"


Session::Session(std::string user, std::string pass) {
    callbacks = {
        &loggedIn,
        &loggedOut,
        NULL,
        &connectionError,
        NULL,
        &notifyMainThread,
        NULL,
        NULL,
        &logMessage
    };
    
    config.api_version = SPOTIFY_API_VERSION;
    config.cache_location = "tmp";
    config.settings_location = "tmp";
    config.application_key = g_appkey;
    config.application_key_size = g_appkey_size;
    config.user_agent = USER_AGENT;
    
    config.callbacks = &callbacks;
    
    sp_error error = sp_session_create(&config, &session);
    if (SP_ERROR_OK != error) {
        fprintf(stderr, "failed to create session: %s\n",
                sp_error_message(error));
    }
    
    std::string username = readUser();
    std::string password = readPassword();
    
    // Login using the credentials given on the command line.
    error = sp_session_login(session, username.c_str(), password.c_str(), 0, NULL);
    
    if (SP_ERROR_OK != error) {
        fprintf(stderr, "failed to login: %s\n",
                sp_error_message(error));
    }
}

/* Callbacks */

void Session::connectionError(sp_session *session, sp_error error) {
    std::cout << "Connection error "
              << sp_error_message(error)
              << std::endl;
}

void Session::loggedIn(sp_session *session, sp_error error) {
    std::cout << "Winning!" << std::endl;
    
}

void Session::loggedOut(sp_session *session) {
    std::cout << "Logged out successfully" << std::endl;
}

void Session::logMessage(sp_session *session, const char *data) {
    fprintf(stderr,"%s",data);
}

void Session::notifyMainThread(sp_session *session) {
    std::lock_guard<std::mutex> lock(notifyMutex);
    notify_events = 1;
    notify_cond.notify_one();
}




// !!!Temporary!!!

std::string Session::readUser() {
    std::string user;
    std::cout << "Username: ";
    std::cin >> user;
    return user;
}

std::string Session::readPassword() {
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    std::string s;
    getline(std::cin, s);
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return s;
}

