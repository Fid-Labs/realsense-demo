cmake_minimum_required(VERSION 3.10)

project(realsense-demo VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find librealsense2 package
find_package(realsense2 REQUIRED)

# Add the executable
add_executable(realsense_demo
    src/main.cpp
    src/DepthCamera.cpp
    src/DepthCameraService.cpp
    src/IntelRealSense.cpp
)

# Specify include directories
target_include_directories(realsense_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${realsense2_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(realsense_demo PRIVATE
    realsense2::realsense2
)

# Add threading support
find_package(Threads REQUIRED)
target_link_libraries(realsense_demo PRIVATE Threads::Threads)