cmake_minimum_required(VERSION 3.10)

project(realsense-demo VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find all required packages
find_package(realsense2 REQUIRED)
find_package(GTest REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(Threads REQUIRED)

# Create library target for shared code
add_library(realsense_lib
    src/IntelRealSense.cpp
    src/DepthCamera.cpp
    src/DepthCameraService.cpp
)

target_include_directories(realsense_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${realsense2_INCLUDE_DIRS}
)

# Link libraries to the main library
target_link_libraries(realsense_lib PUBLIC
    realsense2::realsense2
    Threads::Threads
)

# Main executable
add_executable(realsense_demo
    src/main.cpp
)

target_link_libraries(realsense_demo PRIVATE
    realsense_lib
)

# Google Test executable
add_executable(intel_real_sense_gtest
    tests/intel_real_sense_gtest.cpp
)

target_include_directories(intel_real_sense_gtest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(intel_real_sense_gtest PRIVATE
    realsense_lib
    GTest::gtest_main
    GTest::gmock_main
)

# Boost Test executable
add_executable(intel_real_sense_boost_test
    tests/intel_real_sense_boost_test.cpp
)

target_include_directories(intel_real_sense_boost_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(intel_real_sense_boost_test PRIVATE
    realsense_lib
    Boost::unit_test_framework
)

# Add compile definition for Boost Test
target_compile_definitions(intel_real_sense_boost_test PRIVATE
    BOOST_TEST_DYN_LINK
)

# Enable testing
enable_testing()
add_test(NAME intel_real_sense_gtest COMMAND intel_real_sense_gtest)
add_test(NAME intel_real_sense_boost_test COMMAND intel_real_sense_boost_test)

# Optional: Add a custom target to run all tests
add_custom_target(run_all_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS intel_real_sense_gtest intel_real_sense_boost_test
)