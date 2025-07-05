//
// Created by pspic on 05/07/2025.
//

#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/opencv.hpp>

class ImageProcessor {
public:
    static cv::Mat createHistogramImage(const cv::Mat& grayImage, int histSize = 256, int hist_w = 512, int hist_h = 400);
    static cv::Mat equalizeHistogram(const cv::Mat& grayImage);
    static cv::Mat matchHistogram(const cv::Mat& src, const cv::Mat& target);
};



#endif //IMAGEPROCESSOR_H
