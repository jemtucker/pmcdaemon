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

#include "Configuration.h"
#include "URLStreamModule.h"

#define CONF_PATH "/Users/Jem/workspace/PiPlayer/resources/stations.conf"

Device::Device(): server(new Server()), config(CONF_PATH), dispatcher(new Dispatcher()) {
    dispatcher->addModule(1, new URLStreamModule());
}

void Device::init() {
    server->init(this);
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}

Dispatcher* Device::getDispatcher() {
    return dispatcher.get();
}

Configuration* Device::getConfig() {
    return &config;
}