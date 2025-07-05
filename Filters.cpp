//
// Created by pspic on 05/07/2025.
//

#include "Filters.h"

cv::Mat Filters::blur(const cv::Mat& img, int ksize) {
    cv::Mat blurred;
    cv::blur(img, blurred, cv::Size(ksize, ksize));
    return blurred;
}