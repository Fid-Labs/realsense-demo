# realsense-demo

This repository includes a basic, generic C++ service for controlling and capturing data from a depth camera. You can use Fid to integrate it with an Intel RealSense camera in minutes.

For a tutorial on this, see [docs.fidlabs.ai](https://docs.fidlabs.ai/en/latest/).

## About Fid Labs

This repository is created and maintained by [Fid Labs](https://fidlabs.ai). Fid Labs specializes in building AI-powered tools for developers, streamlining integration with hardware devices like the Intel RealSense camera. Our mission is to simplify complex technical implementations and enable developers to focus on creating innovative applications.

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