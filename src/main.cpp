#include "DepthCameraService.h"
#include "IntelRealSense.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>

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