# realsense-demo

This repository includes a basic, generic C++ service for controlling and capturing data from a depth camera. You can use Fid to integrate it with an Intel RealSense camera in minutes.

For a tutorial on this, see [docs.fidlabs.ai](https://docs.fidlabs.ai/en/latest/).

## Camera Technology

This project leverages Intel RealSense depth sensing camera technology, providing a C++ abstraction layer for camera control and data capture. The implementation focuses specifically on Intel RealSense D400 series cameras, which utilize stereo vision to capture depth information, color imaging, and support region of interest specification for targeted data collection. The camera interface supports configuration of resolution, frame rate, and provides access to depth scale calibration.

The architecture is designed with a clean separation between the general depth camera functionality and Intel RealSense-specific implementation. The DepthCamera abstract base class defines core operations like streaming control, while the IntelRealSense class implements device-specific features such as frame alignment, depth sensor control, and temperature validation to ensure optimal operating conditions (15-35°C) for accurate depth sensing.

### Abstract Camera Interface

```cpp
// From DepthCamera.h
class DepthCamera
{
public:
    DepthCamera();
    virtual ~DepthCamera() = default;

    virtual bool configure(int width, int height, int fps) = 0;
    bool startStreaming();
    void stopStreaming();

protected:
    virtual void captureFrame() = 0;

private:
    void streamFrames();
    std::atomic<bool> isStreaming;
    std::thread streamThread;
};
```

### Intel RealSense Implementation

```cpp
// From IntelRealSense.h
namespace realsense {

class IntelRealSense : public DepthCamera {
    const rs2::align FRAME_ALIGNMENT{RS2_STREAM_COLOR};

public:
    bool configure(int width, int height, int fps) override;

    // Depth Sensor
    float getDepthScale(rs2::device dev);
    void set_depth_sensor(const rs2::depth_sensor& sensor);
    rs2::depth_sensor get_depth_sensor() const;

    // ROI Sensor
    void set_region_of_interest(const rs2::region_of_interest& roi);
    rs2::region_of_interest get_region_of_interest() const;
    bool has_roi() const;

    // Temperature Test - returns true if temperature is within valid operating range (15-35°C)
    bool isTemperatureValid(float temperature) const;

protected:
    void captureFrame() override;

private:
    int width;
    int height;
    int fps;
};

}
```

## Test Infrastructure

The project employs a dual testing framework approach, leveraging both Google Test and Boost Test frameworks to ensure comprehensive validation of camera functionality. Tests focus on critical components like temperature validation, demonstrating multiple assertion styles including simple validations, boundary condition testing, and parameterized test cases that validate system behavior across multiple inputs with a single test definition.

The test infrastructure is fully integrated into the CMake build system, enabling automated test execution through a custom target (run_all_tests). Each test framework provides complementary capabilities: Google Test offers more modern features like test fixtures and mock objects, while Boost Test provides integration with the broader Boost ecosystem. This approach ensures maximum validation coverage while accommodating developer preferences for different testing paradigms.

### Google Test Example

```cpp
// From intelRealSenseGoogleTest.cpp
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
```

### Parameterized Testing with Google Test

```cpp
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
```

### Boost Test Example

```cpp
// From intelRealSenseBoostTest.cpp
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
```

### Test Build Configuration

```cmake
# From CMakeLists.txt
# Google Test executable
add_executable(intelRealSenseGoogleTest
    tests/intelRealSenseGoogleTest.cpp
)

target_include_directories(intelRealSenseGoogleTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(intelRealSenseGoogleTest PRIVATE
    realsense_lib
    GTest::gtest_main
    GTest::gmock_main
)

# Boost Test executable
add_executable(intelRealSenseBoostTest
    tests/intelRealSenseBoostTest.cpp
)

# Enable testing
enable_testing()
add_test(NAME intelRealSenseGoogleTest COMMAND intelRealSenseGoogleTest)
add_test(NAME intelRealSenseBoostTest COMMAND intelRealSenseBoostTest)

# Optional: Add a custom target to run all tests
add_custom_target(run_all_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS intelRealSenseGoogleTest intelRealSenseBoostTest
)
```

## Documentation Overview

Documentation for this project is structured with multiple layers to support different user needs. At the top level, the README provides essential setup and build instructions for both Linux and macOS environments, ensuring users can quickly get the system operational. The repository also includes direct links to the Intel RealSense SDK resources, including the API reference documentation and the SDK repository for deeper technical understanding.

For more detailed implementation guidance, the project references the comprehensive Fid Labs documentation site (docs.fidlabs.ai), which provides tutorials on camera integration. The codebase itself is supported by technical reference material in the docs directory, including hardware specifications like the Intel RealSense D400 Series Datasheet, which details the camera's capabilities, limitations, and operating parameters for proper integration and usage.

## Codebase Structure: File-by-File Guide

### `src/DepthCamera.h` and `src/DepthCamera.cpp`
Defines the abstract base class for depth camera functionality. Implements a template method pattern where concrete subclasses implement the `captureFrame()` method while inheriting common streaming functionality. Key features include thread-safe streaming control using std::atomic and std::thread.

### `src/IntelRealSense.h` and `src/IntelRealSense.cpp`
Implements the concrete Intel RealSense camera functionality by inheriting from the DepthCamera base class. Includes specialized features like depth scale calibration, region of interest (ROI) specification, and temperature validation to ensure optimal operating conditions.

### `src/DepthCameraService.h` and `src/DepthCameraService.cpp`
Provides a service layer that encapsulates camera operation for client applications. Demonstrates dependency injection pattern by accepting any DepthCamera implementation via std::unique_ptr, promoting loose coupling and testability.

### `src/main.cpp`
Demonstrates a simple application using the camera service. Shows proper memory management with smart pointers, error handling, and resource cleanup.

### `tests/intelRealSenseGoogleTest.cpp`
Implements unit tests using Google Test framework. Demonstrates test fixtures, parameterized tests, and multiple assertion styles for comprehensive validation of camera functionality.

### `tests/intelRealSenseBoostTest.cpp`
Provides complementary tests using the Boost Test framework, showcasing alternative testing approaches within the same codebase.

### `CMakeLists.txt`
Orchestrates the build system configuration, including library and dependency management, test integration, and custom targets for convenient operation.

## C++ Programming Techniques and Tips

### 1. RAII and Resource Management
This codebase demonstrates modern C++ resource management through the RAII (Resource Acquisition Is Initialization) pattern:
- Smart pointers (std::unique_ptr) manage dynamic memory in DepthCameraService
- Thread resources are properly acquired and released in DepthCamera's streaming functions
- No raw new/delete operations, ensuring leak-free code

```cpp
// Thread management with RAII (from DepthCamera.cpp)
void DepthCamera::stopStreaming()
{
    if (!isStreaming)
    {
        return;
    }
    isStreaming = false;
    if (streamThread.joinable())
    {
        streamThread.join();
    }
}
```

### 2. Polymorphism and Inheritance
- Abstract base class (`DepthCamera`) defines the interface with pure virtual methods
- Concrete implementation (`IntelRealSense`) provides specific functionality
- Virtual destructors ensure proper cleanup of derived class resources

```cpp
// Abstract base class with pure virtual methods
class DepthCamera
{
public:
    // Pure virtual method to be implemented by derived classes
    virtual bool configure(int width, int height, int fps) = 0;
    
    // Common interface methods
    bool startStreaming();
    void stopStreaming();

protected:
    // Protected pure virtual method for template method pattern
    virtual void captureFrame() = 0;
};

// Concrete implementation
class IntelRealSense : public DepthCamera {
public:
    // Implementation of the pure virtual method
    bool configure(int width, int height, int fps) override;

protected:
    // Implementation of the protected virtual method
    void captureFrame() override;
};
```

### 3. Thread Safety
- `std::atomic<bool>` for thread-safe flag operations without mutex overhead
- Clean thread joining pattern in `stopStreaming()` preventing thread leaks
- Single responsibility principle applied to thread management methods

```cpp
// Thread-safe streaming with atomic flag and thread management
// From DepthCamera.h
class DepthCamera
{
private:
    std::atomic<bool> isStreaming;
    std::thread streamThread;
};

// From DepthCamera.cpp
bool DepthCamera::startStreaming()
{
    if (isStreaming)
    {
        std::cout << "Already streaming" << std::endl;
        return false;
    }
    isStreaming = true;
    streamThread = std::thread(&DepthCamera::streamFrames, this);
    return true;
}

void DepthCamera::streamFrames()
{
    while (isStreaming)
    {
        captureFrame();
        std::this_thread::sleep_for(std::chrono::milliseconds(33)); // ~30 FPS
    }
}
```

### 4. Interface Segregation
- Clean separation between general camera interface and specific implementations
- Public API contains only essential methods while implementation details remain protected/private
- Strong encapsulation by using the pImpl idiom (Pointer to Implementation) implicitly through inheritance

### 5. Dependency Injection
- Service class accepts camera implementation via constructor injection
- Use of std::move for efficient transfer of unique ownership
- Allows for easy testing with mock objects and runtime substitution of implementations

```cpp
// Dependency injection pattern (from DepthCameraService.h and .cpp)
class DepthCameraService
{
public:
    // Constructor injection of camera implementation
    DepthCameraService(std::unique_ptr<DepthCamera> camera);
    bool init(int width, int height, int fps);
    bool start();
    void stop();

private:
    std::unique_ptr<DepthCamera> camera;
};

// Implementation showing ownership transfer with std::move
DepthCameraService::DepthCameraService(std::unique_ptr<DepthCamera> camera)
    : camera(std::move(camera)) {}
```

### 6. Modern Testing Approaches
- Fixture-based tests for shared setup/teardown
- Parameterized tests for efficient validation of multiple inputs
- Multiple assertion styles (EXPECT vs ASSERT) for different verification needs
- Custom failure messages for improved debugging

### 7. Building with CMake
- Separation of library and executable targets
- Proper handling of include paths and visibility (PUBLIC vs PRIVATE)
- Integration of multiple test frameworks in a single project
- Custom targets (run_all_tests) for improved developer experience

```cmake
# Library target with proper visibility settings
add_library(realsense_lib
    src/IntelRealSense.cpp
    src/DepthCamera.cpp
    src/DepthCameraService.cpp
)

target_include_directories(realsense_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${realsense2_INCLUDE_DIRS}
)

# Main executable with private linkage to the library
add_executable(realsense_demo
    src/main.cpp
)

target_link_libraries(realsense_demo PRIVATE
    realsense_lib
)
```

## Linux Setup

Follow the [librealsense install guide](https://github.com/IntelRealSense/librealsense/blob/master/doc/distribution_linux.md) (Be sure to include the optional `librealsense2-dev`).

### Example Application Usage

```cpp
// From main.cpp
int main()
{
    auto camera = std::make_unique<realsense::IntelRealSense>();
    DepthCameraService service(std::move(camera));

    if (!service.init(640, 480, 30))
    {
        std::cerr << "Failed to initialize the camera" << std::endl;
        return 1;
    }

    if (!service.start())
    {
        std::cerr << "Failed to start streaming" << std::endl;
        return 1;
    }

    std::cout << "Streaming for 5 seconds..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));

    service.stop();
    std::cout << "Streaming stopped" << std::endl;

    return 0;
}
```

## Mac Setup

```
brew install librealsense
```

## Build

```
mkdir build && cd build
cmake ..
make -j
```

## RealSense Resources

[API Reference](https://intelrealsense.github.io/librealsense/doxygen/annotated.html)
[SDK Repository](https://github.com/IntelRealSense/librealsense)