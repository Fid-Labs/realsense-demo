# realsense-demo

This repository includes a basic, generic C++ service for controlling and capturing data from a depth camera. You can use Fid to integrate it with an Intel RealSense camera in minutes.

For a tutorial on this, see [docs.fidlabs.ai](https://docs.fidlabs.ai/en/latest/).

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

[API Reference](https://intelrealsense.github.io/librealsense/doxygen/index.html)
[SDK Repository](https://github.com/IntelRealSense/librealsense)