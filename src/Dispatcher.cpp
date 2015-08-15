//
//  Dispatcher.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 05/08/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Dispatcher.h"

#include <thread>

#include "Request.h"
#include "URLStreamModule.h"

Dispatcher::Dispatcher() {
    modules[URL_STREAM] = std::unique_ptr<Module>(new URLStreamModule());
}

bool Dispatcher::queueIsEmpty() {
    std::lock_guard<std::mutex> lock(queueMutex);
    return requestQueue.empty();
}

void Dispatcher::emptyQueue() {
    while(!queueIsEmpty()) {
        dispatch(pop());
    }
}

void Dispatcher::push(Request *request) {
    std::lock_guard<std::mutex> lock(queueMutex);
    requestQueue.push(request);
}

Request *Dispatcher::pop() {
    std::lock_guard<std::mutex> lock(queueMutex);
    Request *r = requestQueue.front();
    requestQueue.pop();
    return r;
}

void Dispatcher::dispatch(Request *request) {
    modules[request->moduleType()]->execute(request);
}

void Dispatcher::queueRequest(Request *request) {
    bool first = queueIsEmpty();
    push(request);
    if (first) {
        emptyQueue();
    }
        
        //std::thread t(&Dispatcher::emptyQueue, this);
}