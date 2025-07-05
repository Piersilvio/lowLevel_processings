//
// Created by pspic on 05/07/2025.
//

#ifndef PIXELOPERATIONS_H
#define PIXELOPERATIONS_H



#include <opencv2/opencv.hpp>

class PixelOperations {
public:
    static cv::Mat invert(const cv::Mat& img);
};



#endif //PIXELOPERATIONS_H
