//
// Created by pspic on 05/07/2025.
//

#include "ImageProcessor.h"

cv::Mat ImageProcessor::createHistogramImage(const cv::Mat& grayImage, int histSize, int hist_w, int hist_h) {
    cv::Mat hist;
    float range[] = {0, 256};
    const float* histRange = {range};

    cv::calcHist(&grayImage, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);

    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0,0,0));
    cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX);

    int bin_w = cvRound((double) hist_w / histSize);
    for (int i = 1; i < histSize; i++) {
        cv::line(histImage,
                 cv::Point(bin_w * (i-1), hist_h - cvRound(hist.at<float>(i-1))),
                 cv::Point(bin_w * i, hist_h - cvRound(hist.at<float>(i))),
                 cv::Scalar(255,255,255), 2);
    }
    return histImage;
}

cv::Mat ImageProcessor::equalizeHistogram(const cv::Mat& grayImage) {
    cv::Mat equalized;
    cv::equalizeHist(grayImage, equalized);
    return equalized;
}

cv::Mat ImageProcessor::matchHistogram(const cv::Mat& src, const cv::Mat& target) {
    CV_Assert(src.type() == CV_8UC1 && target.type() == CV_8UC1);

    cv::Mat histSrc, histTarget;
    int histSize = 256;
    float range[] = {0,256};
    const float* histRange = {range};

    cv::calcHist(&src, 1, 0, cv::Mat(), histSrc, 1, &histSize, &histRange);
    cv::calcHist(&target, 1, 0, cv::Mat(), histTarget, 1, &histSize, &histRange);

    // Compute CDF
    cv::Mat cdfSrc(histSrc.size(), histSrc.type());
    cdfSrc.at<float>(0) = histSrc.at<float>(0);
    for (int i = 1; i < histSrc.rows; i++)
        cdfSrc.at<float>(i) = cdfSrc.at<float>(i-1) + histSrc.at<float>(i);
    cdfSrc /= cdfSrc.at<float>(histSrc.rows - 1);

    cv::Mat cdfTarget(histTarget.size(), histTarget.type());
    cdfTarget.at<float>(0) = histTarget.at<float>(0);
    for (int i = 1; i < histTarget.rows; i++)
        cdfTarget.at<float>(i) = cdfTarget.at<float>(i-1) + histTarget.at<float>(i);
    cdfTarget /= cdfTarget.at<float>(histTarget.rows - 1);

    uchar lut[256];
    for (int i = 0; i < 256; i++) {
        float sVal = cdfSrc.at<float>(i);
        uchar z = 0;
        float minDiff = 1.0f;
        for (int j = 0; j < 256; j++) {
            float diff = abs(sVal - cdfTarget.at<float>(j));
            if (diff < minDiff) {
                minDiff = diff;
                z = (uchar) j;
            }
        }
        lut[i] = z;
    }

    cv::Mat matched;
    cv::LUT(src, cv::Mat(1,256,CV_8U,lut), matched);
    return matched;
}