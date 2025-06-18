# realsense-demo

This repository includes a basic, generic C++ service for controlling and capturing data from a depth camera. You can use Fid to integrate it with an Intel RealSense camera in minutes.

For a tutorial on this, see [docs.fidlabs.ai](https://docs.fidlabs.ai/en/latest/).

## Camera Technology

This project leverages Intel RealSense depth sensing camera technology, providing a C++ abstraction layer for camera control and data capture. The implementation focuses specifically on Intel RealSense D400 series cameras, which utilize stereo vision to capture depth information, color imaging, and support region of interest specification for targeted data collection. The camera interface supports configuration of resolution, frame rate, and provides access to depth scale calibration.

The architecture is designed with a clean separation between the general depth camera functionality and Intel RealSense-specific implementation. The DepthCamera abstract base class defines core operations like streaming control, while the IntelRealSense class implements device-specific features such as frame alignment, depth sensor control, and temperature validation to ensure optimal operating conditions (15-35°C) for accurate depth sensing.

## Test Infrastructure

The project employs a dual testing framework approach, leveraging both Google Test and Boost Test frameworks to ensure comprehensive validation of camera functionality. Tests focus on critical components like temperature validation, demonstrating multiple assertion styles including simple validations, boundary condition testing, and parameterized test cases that validate system behavior across multiple inputs with a single test definition.

The test infrastructure is fully integrated into the CMake build system, enabling automated test execution through a custom target (run_all_tests). Each test framework provides complementary capabilities: Google Test offers more modern features like test fixtures and mock objects, while Boost Test provides integration with the broader Boost ecosystem. This approach ensures maximum validation coverage while accommodating developer preferences for different testing paradigms.

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

### 2. Polymorphism and Inheritance
- Abstract base class (`DepthCamera`) defines the interface with pure virtual methods
- Concrete implementation (`IntelRealSense`) provides specific functionality
- Virtual destructors ensure proper cleanup of derived class resources

### 3. Thread Safety
- `std::atomic<bool>` for thread-safe flag operations without mutex overhead
- Clean thread joining pattern in `stopStreaming()` preventing thread leaks
- Single responsibility principle applied to thread management methods

### 4. Interface Segregation
- Clean separation between general camera interface and specific implementations
- Public API contains only essential methods while implementation details remain protected/private
- Strong encapsulation by using the pImpl idiom (Pointer to Implementation) implicitly through inheritance

### 5. Dependency Injection
- Service class accepts camera implementation via constructor injection
- Use of std::move for efficient transfer of unique ownership
- Allows for easy testing with mock objects and runtime substitution of implementations

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

## Linux Setup

Follow the [librealsense install guide](https://github.com/IntelRealSense/librealsense/blob/master/doc/distribution_linux.md) (Be sure to include the optional `librealsense2-dev`).

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