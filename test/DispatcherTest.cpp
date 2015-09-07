//
//  DispatcherTest.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 02/09/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include <gtest/gtest.h>

#include <thread>

#include "Dispatcher.h"
#include "Module.h"

class DispatcherTest : public ::testing::Test {
protected:
    void static queueRequests(int times, int sleepSecs, int id, Dispatcher *d) {
        for (int i = 0; i < times; i++) {
            d->queueRequest(new TestRequest(id));
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepSecs));
        }
    }
    
    class TestRequest : public Request {
        int id;
    public:
        TestRequest(int id): Request(nullptr) {
            this->id = id;
        }
        virtual int moduleType() {
            return id;
        }
    };
    
    class TestModule : public Module {
        int timesExecuted = 0;
    public:
        virtual void execute(Request *request) {
            timesExecuted ++;
        }
        
        int times() {
            return timesExecuted;
        }
    };
};

// Tests that Dispatcher dispatches to the correct module
TEST_F(DispatcherTest, ShouldDispatchRequestsToTheCorrectModule) {
    Dispatcher dispatcher{};
    
    TestModule *tm1 = new TestModule();
    TestModule *tm2 = new TestModule();
    
    dispatcher.addModule(ModuleType::URL_STREAM, tm1);
    dispatcher.addModule(ModuleType::URL_FUNCTION, tm2);
    
    dispatcher.queueRequest(new TestRequest(1));
    dispatcher.queueRequest(new TestRequest(1));
    dispatcher.queueRequest(new TestRequest(1));
    dispatcher.queueRequest(new TestRequest(1));
    dispatcher.queueRequest(new TestRequest(1));
    
    EXPECT_EQ(5, tm1->times());
    EXPECT_EQ(0, tm2->times());
    
    dispatcher.queueRequest(new TestRequest(2));
    dispatcher.queueRequest(new TestRequest(2));
    dispatcher.queueRequest(new TestRequest(2));
    dispatcher.queueRequest(new TestRequest(2));
    dispatcher.queueRequest(new TestRequest(2));
    dispatcher.queueRequest(new TestRequest(2));
    dispatcher.queueRequest(new TestRequest(2));
    dispatcher.queueRequest(new TestRequest(2));
    dispatcher.queueRequest(new TestRequest(2));
    dispatcher.queueRequest(new TestRequest(2));
    
    EXPECT_EQ(5, tm1->times());
    EXPECT_EQ(10, tm2->times());
}

// Test the dispatcher can handle multiple threads
TEST_F(DispatcherTest, ShouldHandleMultipleThreadsQueueingRequests) {
    Dispatcher dispatcher{};
    
    TestModule *tm1 = new TestModule();
    TestModule *tm2 = new TestModule();
    
    dispatcher.addModule(ModuleType::URL_STREAM, tm1);
    dispatcher.addModule(ModuleType::URL_FUNCTION, tm2);
    
    std::thread t1(queueRequests, 100, 10, 1, &dispatcher);
    std::thread t2(queueRequests, 150,  1, 2, &dispatcher);
    std::thread t3(queueRequests,  75, 74, 1, &dispatcher);
    
    t1.join();
    t2.join();
    t3.join();
    
    EXPECT_EQ(175, tm1->times());
    EXPECT_EQ(150, tm2->times());
}



