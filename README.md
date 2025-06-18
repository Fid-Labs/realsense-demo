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