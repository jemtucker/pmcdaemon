//
//  Dispatcher.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 05/08/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Dispatcher.h"


void Dispatcher::addModule(int type, Module *module) {
    modules[type] = std::unique_ptr<Module>(module);
}

Module *Dispatcher::getModule(int type) {
    return modules[type].get();
}

void Dispatcher::emptyQueue() {
    Request *r;
    while((r = pop()) != nullptr) {
        dispatch(r);
    }
}

bool Dispatcher::push(Request *request) {
    std::lock_guard<std::mutex> lock(queueMutex);
    bool first = requestQueue.empty();
    requestQueue.push(request);
    return first;
}

Request *Dispatcher::pop() {
    std::lock_guard<std::mutex> lock(queueMutex);
    if (requestQueue.empty()) return nullptr;
    Request *r = requestQueue.front();
    requestQueue.pop();
    return r;
}

void Dispatcher::dispatch(Request *request) {
    modules[request->moduleType()]->execute(request);
}

void Dispatcher::queueRequest(Request *request) {
    if (push(request)) {
        emptyQueue();
    }
}