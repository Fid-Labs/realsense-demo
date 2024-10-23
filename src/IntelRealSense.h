#ifndef INTEL_REAL_SENSE_H
#define INTEL_REAL_SENSE_H

#include "DepthCamera.h"
#include <librealsense2/rs.hpp> 
#include <memory>
#include <string>

namespace realsense {

class IntelRealSense : public DepthCamera {
    const rs2::align FRAME_ALIGNMENT{RS2_STREAM_COLOR};

public:
    bool configure(int width, int height, int fps) override;

    //Depth Sensor
    float getDepthScale(rs2::device dev);
    void set_depth_sensor(const rs2::depth_sensor& sensor);
    rs2::depth_sensor get_depth_sensor() const;

    //ROI Sensor
    void set_region_of_interest(const rs2::region_of_interest& roi);
    rs2::region_of_interest get_region_of_interest() const;
    bool has_roi() const;

protected:
    void captureFrame() override;

private:
    int width;
    int height;
    int fps;
};

} 

#endif