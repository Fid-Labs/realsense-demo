#ifndef INTEL_REAL_SENSE_H
#define INTEL_REAL_SENSE_H

#include <librealsense2/rs.hpp> 

namespace realsense {

class IntelRealSense {

public:
    // Returns true if temperature is within valid operating range (15-35°C)
    bool isTemperatureValid(float temperature) const;
};

} 

#endif