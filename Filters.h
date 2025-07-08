//
// Created by pspic on 05/07/2025.
//

#ifndef FILTERS_H
#define FILTERS_H



#include <opencv2/opencv.hpp>

class Filters {
public:
    static cv::Mat blur(const cv::Mat& img, int ksize=5);
    static cv::Mat sobel(const cv::Mat& img);
    static cv::Mat roberts(const cv::Mat& img);
    static cv::Mat sharpenLaplacian(const cv::Mat& img, int c);
};



#endif //FILTERS_H
