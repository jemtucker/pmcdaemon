//
//  Device.h
//  pmcdaemon
//
//  Created by Jem Tucker on 17/07/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Device__
#define __pmcdaemon__Device__

#include <map>
#include <memory>
#include <mutex>
#include <queue>

enum ModuleType {
    RADIO
};

class Configuration;
class Module;
class Request;
class Server;

class Device {
    std::shared_ptr<Configuration> config;
    std::map<ModuleType, std::unique_ptr<Module>> modules;
    std::unique_ptr<Server> server;
    
    std::mutex mutexQueue;
    std::queue<std::unique_ptr<Request>> requestQueue;
    
    void addModule(ModuleType, Module *);
    
    std::unique_ptr<Request> getNextRequest();
    void handleRequests();

public:
    Device();
    void queueRequest(Request *);
    void play(ModuleType, std::string &);
};

#endif /* defined(__pmcdaemon__Device__) */
