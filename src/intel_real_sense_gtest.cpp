#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IntelRealSense.h"

class IntelRealSenseTest : public ::testing::Test {
protected:
    void SetUp() override {
    }
    realsense::IntelRealSense camera;
};

TEST_F(IntelRealSenseTest, TemperatureValidationTest) {
    // Test valid temperature
    EXPECT_TRUE(camera.isTemperatureValid(25.0f));

    // Test too cold
    EXPECT_FALSE(camera.isTemperatureValid(10.0f));

    // Test too hot
    EXPECT_FALSE(camera.isTemperatureValid(40.0f));

    // Test boundary conditions
    EXPECT_TRUE(camera.isTemperatureValid(15.0f)); // Lower bound
    EXPECT_TRUE(camera.isTemperatureValid(35.0f)); // Upper bound
}

// Additional test case to show different assertion styles
TEST_F(IntelRealSenseTest, TemperatureBoundaryTest) {
    // Test just inside boundaries
    ASSERT_TRUE(camera.isTemperatureValid(15.1f));
    ASSERT_TRUE(camera.isTemperatureValid(34.9f)); 

    // Test just outside boundaries
    ASSERT_FALSE(camera.isTemperatureValid(14.9f));
    ASSERT_FALSE(camera.isTemperatureValid(35.1f));
}

// Test with parameterized values
TEST_F(IntelRealSenseTest, TemperatureRangeTest){
    struct TestCase{
        float temperature;
        bool expected;
    };

    std::vector<TestCase> testCases = {
        {20.0f, true},
        {30.0f, true},
        {0.0f, false},
        {50.0f, false},
        {15.0f, true},
        {35.0f, true}
    };

    for (const auto& tc : testCases){
        EXPECT_EQ(camera.isTemperatureValid(tc.temperature), tc.expected)
            << "Failed for temperature: " << tc.temperature;
    }
}