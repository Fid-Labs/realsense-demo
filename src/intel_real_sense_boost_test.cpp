#define BOOST_TEST_MODULE IntelRealSenseTest
#include <boost/test/unit_test.hpp>
#include "IntelRealSense.h"

BOOST_AUTO_TEST_SUITE(IntelRealSenseTestSuite)

BOOST_AUTO_TEST_CASE(TemperatureValidationTest)
{
    realsense::IntelRealSense camera;
    
    // Test valid temperature
    BOOST_CHECK_EQUAL(camera.isTemperatureValid(25.0f), true);

    // Test too cold
    BOOST_CHECK_EQUAL(camera.isTemperatureValid(10.0f), false);

    // Test too hot
    BOOST_CHECK_EQUAL(camera.isTemperatureValid(40.0f), false);

    // Test boundary conditions
    BOOST_CHECK_EQUAL(camera.isTemperatureValid(15.0f), true); // Lower bound
    BOOST_CHECK_EQUAL(camera.isTemperatureValid(35.0f), true); // Upper bound
}

BOOST_AUTO_TEST_SUITE_END()