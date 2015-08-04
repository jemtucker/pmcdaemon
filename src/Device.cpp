//
//  Device.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 17/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Device.h"

#include "Configuration.h"
#include "Module.h"
#include "Request.h"
#include "Server.h"

/* Modules */
#include "RadioModule.h"

/* Handlers */
#include "StationRequestHandler.h"

#define CONF_PATH "/Users/Jem/workspace/PiPlayer/resources/stations.conf"
#define INTERVAL_MS 1000

Device::Device(): server(new Server()) {}

void Device::init() {
    const std::string path = CONF_PATH;
    config = std::make_shared<Configuration>(path);
    
    server->init();
    
    StationRequestHandler handler(this);
    addModule(RADIO, new RadioModule(config), "/api/radio/", handler);
    
    handleRequests();
}

void Device::addModule(ModuleType type, Module *module, std::string url, CivetHandler &handler) {
    modules[type] = std::unique_ptr<Module>(module);
    try {
        modules[type]->init();
        server->addHandler(url, handler);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void Device::handleRequests() {
    while (true) {
        std::unique_ptr<Request> request = getNextRequest();
        if(request) {
            request->execute(this);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(INTERVAL_MS));
    }
}

void Device::queueRequest(Request *r) {
    std::lock_guard<std::mutex> lock(mutexQueue);
    requestQueue.push(std::unique_ptr<Request>(r));
}

std::unique_ptr<Request> Device::getNextRequest() {
    std::lock_guard<std::mutex> lock(mutexQueue);
    if (!requestQueue.empty()) {
        std::unique_ptr<Request> request = std::move(requestQueue.front());
        requestQueue.pop();
        return std::move(request);
    }
    return nullptr;
}

void Device::play(ModuleType moduleType, std::string &str) {
    modules[moduleType]->play(str);
}
