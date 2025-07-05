//
// Created by pspic on 05/07/2025.
//

#include "PixelOperations.h"

cv::Mat PixelOperations::invert(const cv::Mat& img) {
    cv::Mat inverted;
    cv::bitwise_not(img, inverted);
    return inverted;
}