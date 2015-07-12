//
//  Server.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 04/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Server.h"
#include "StationRequestHandler.h"

Server::Server(Player *p) {
    const char *options[] = {
        "num_threads", "1",
        NULL
    };
    
    settings.civetOptions = options;
    settings.workInterval = std::chrono::duration<long, std::milli>(1000);
    
    std::unique_ptr<CivetServer> cs(new CivetServer(settings.civetOptions));
    server = std::move(cs);
    
    server->addHandler("/station/", new StationRequestHandler(this, p));
    
    startWorker();
}

void Server::startWorker() {
    std::unique_ptr<std::thread> theWorker(new std::thread(&Server::doWork, this));
    worker = std::move(theWorker);
}

void Server::queueRequest(Request *r) {
    std::lock_guard<std::mutex> lock(mutexQueue);
    requestQueue.push(std::unique_ptr<Request>(r));
}

void Server::doWork() {
    while (true) {
        std::unique_ptr<Request> request = getNextRequest();
        if(request) {
            request->execute();
        }
        std::this_thread::sleep_for(settings.workInterval);
    }
}

std::unique_ptr<Request> Server::getNextRequest() {
    std::lock_guard<std::mutex> lock(mutexQueue);
    if (!requestQueue.empty()) {
        std::unique_ptr<Request> request = std::move(requestQueue.front());
        requestQueue.pop();
        return std::move(request);
    }
    return nullptr;
}