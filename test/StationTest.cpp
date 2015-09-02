//
//  StationTest.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 01/09/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Station.h"

#include "gtest/gtest.h"

class StationTest : public ::testing::Test {
protected:
    
};

TEST_F(StationTest, ReturnsAUrlWhenAsked) {
    std::string station_name = "Station One";
    std::string station_url  = "http://the/station/url.mp3 ";
    Station station(station_name, station_url, 1);
    EXPECT_EQ(station_url, station.getUrl());
}