//
//  Device.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 17/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Device.h"

#include <thread>
#include <chrono>
#include <fstream>

#include "Configuration.h"
#include "URLStreamModule.h"

#define CONF_PATH "/Users/Jem/workspace/PiPlayer/resources/stations.conf"

Device::Device(): server(new Server()), config() {}

void Device::init() {
    std::ifstream file(CONF_PATH, std::ifstream::in);
    
    config.loadConfig(file);
    
    streamModule = std::unique_ptr<URLStreamModule>(new URLStreamModule());
    
    server->init(this);
    
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}

URLStreamModule* Device::getStreamModule() {
    return streamModule.get();
}

Configuration* Device::getConfig() {
    return &config;
}