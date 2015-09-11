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

void Dispatcher::dispatch(Request *request) {
    std::lock_guard<std::mutex> lock(mutex);
    modules[request->moduleType()]->execute(request);
}