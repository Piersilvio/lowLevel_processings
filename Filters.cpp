//
// Created by pspic on 05/07/2025.
//

#include "Filters.h"

cv::Mat Filters::blur(const cv::Mat& img, int ksize) {
    cv::Mat blurred;
    cv::GaussianBlur(img, blurred, cv::Size(ksize, ksize), 0);
    return blurred;
}

cv::Mat Filters::sobel(const cv::Mat& img) {
    cv::Mat gray, grad_x, grad_y, abs_grad_x, abs_grad_y, grad;

    if (img.channels() == 3) {
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = img.clone();
    }

    cv::Sobel(gray, grad_x, CV_16S, 1, 0);
    cv::Sobel(gray, grad_y, CV_16S, 0, 1);

    cv::convertScaleAbs(grad_x, abs_grad_x);
    cv::convertScaleAbs(grad_y, abs_grad_y);

    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    return grad;
}

cv::Mat Filters::roberts(const cv::Mat& img) {
    cv::Mat gray, grad_x, grad_y, grad;

    if (img.channels() == 3) {
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = img.clone();
    }

    // Roberts kernels
    cv::Mat kernel_x = (cv::Mat_<char>(2, 2) << 1, 0, 0, -1);
    cv::Mat kernel_y = (cv::Mat_<char>(2, 2) << 0, 1, -1, 0);

    // Apply filters
    cv::filter2D(gray, grad_x, CV_16S, kernel_x);
    cv::filter2D(gray, grad_y, CV_16S, kernel_y);

    // Convert gradients to absolute values
    cv::convertScaleAbs(grad_x, grad_x);
    cv::convertScaleAbs(grad_y, grad_y);

    // Combine gradients
    cv::addWeighted(grad_x, 0.5, grad_y, 0.5, 0, grad);
    return grad;
}

cv::Mat Filters::sharpenLaplacian(const cv::Mat& img, int c) {
    cv::Mat gray;
    if (img.channels() == 3)
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    else
        gray = img.clone();

    cv::Mat lap, sharpened;

    cv::Laplacian(gray, lap, CV_16S, 3);

    cv::Mat lap_scaled;
    if (c == -1) {
        // sharpening = original - laplacian
        cv::addWeighted(gray, 1.0, lap, -1.0, 0, sharpened, CV_8U);
    } else {
        // sharpening = original + laplacian
        cv::addWeighted(gray, 1.0, lap, 1.0, 0, sharpened, CV_8U);
    }

    return sharpened;
}