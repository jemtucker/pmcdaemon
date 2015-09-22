//
//  ConfigurationTest.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 06/09/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include <gtest/gtest.h>
#include <strstream>

#include "Configuration.h"

class ConfigurationTest : public ::testing::Test {
protected:

    
};

// Test config can load lines from a stream and populate a map
TEST_F(ConfigurationTest, LoadsLinesFromAnInputStream) {
    Configuration config;
    std::string s = "radio1=url1\nradio2=url2\nradio3=url3";
    std::istringstream ss(s);
    config.loadConfig(ss);
    
    EXPECT_EQ("url1", config.getUrl("radio1"));
    EXPECT_EQ("url2", config.getUrl("radio2"));
    EXPECT_EQ("url3", config.getUrl("radio3"));
    EXPECT_EQ("", config.getUrl("radio4"));
}

TEST_F(ConfigurationTest, GetAllStationsShouldReturnAVectorOfNames) {
    Configuration config;
    std::string s = "radio1=url1\nradio2=url2\nradio3=url3";
    std::istringstream ss(s);
    config.loadConfig(ss);
    
    std::vector<std::string> result = config.getAllStations();
    std::vector<std::string> expected = { "radio1", "radio2", "radio3" };
    
    for (int i = 0; i < expected.size(); i ++) {
        SCOPED_TRACE(i);
        ASSERT_EQ(expected[i], result[i]);
    }
}

TEST_F(ConfigurationTest, GetAllStationsShouldReturnDistinctNames) {
    Configuration config;
    std::string s = "radio1=url1\nradio2=url2\nradio3=url3\nradio3=url4";
    std::istringstream ss(s);
    config.loadConfig(ss);
    
    std::vector<std::string> result = config.getAllStations();
    std::vector<std::string> expected = { "radio1", "radio2", "radio3" };
    
    for (int i = 0; i < expected.size(); i ++) {
        SCOPED_TRACE(i);
        ASSERT_EQ(expected[i], result[i]);
    }
}
