
#include <librealsense2/rs.hpp>
#include <librealsense2/hpp/rs_pipeline.hpp> // Include this missing header for correct compilation

namespace realsense {

// Forward declare the IntelRealSense class
class IntelRealSense {
public:
    // Returns true if temperature is within valid operating range (15-35°C)
    bool isTemperatureValid(float temperature) const;
};

// Move the implementation outside the class definition to ensure it's linked correctly
bool IntelRealSense::isTemperatureValid(float temperature) const {
    // Check if the temperature is within the specified valid range
    // Adjust the range to correctly validate temperatures precisely at 15 and 35
    return (temperature >= 15.0f) && (temperature <= 35.0f);
}

}
