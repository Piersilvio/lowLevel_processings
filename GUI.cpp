//
// Created by pspic on 05/07/2025.
//

#include "GUI.h"

#include "ImageProcessor.h"
#include "PixelOperations.h"
#include "Filters.h"

#include <opencv2/opencv.hpp>
#include <iostream>

void GUI::run() {

    std::string imagePath;
    std::cout << "Enter path to color image: ";
    std::getline(std::cin, imagePath);
    cv::Mat img;

    try {
        img = cv::imread(imagePath, cv::IMREAD_COLOR);
        if (img.empty()) {
            throw std::runtime_error("Could not read the image: " + imagePath);
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception loading image: " << e.what() << std::endl;
        return;
    }

    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    while (true) {
        std::cout << "\nChoose operation:\n";
        std::cout << "1) Show Histogram\n";
        std::cout << "2) Equalize Histogram\n";
        std::cout << "3) Histogram Matching\n";
        std::cout << "4) Invert Image\n";
        std::cout << "5) Gaussian Image\n";
        std::cout << "6) Sobel Image\n";
        std::cout << "7) Roberts Image\n";
        std::cout << "8) Sharpen Image\n";
        std::cout << "0) Exit\n";
        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                cv::Mat histImage = ImageProcessor::createHistogramImage(gray);
                cv::imshow("Histogram", histImage);
                cv::waitKey(0);
                break;
            }
            case 2: {
                cv::Mat eq = ImageProcessor::equalizeHistogram(gray);
                cv::imshow("Equalized Image", eq);
                cv::waitKey(0);
                break;
            }
            case 3: {
                std::string targetPath;
                std::cout << "Enter path to target grayscale image: ";
                std::cin.ignore();
                std::getline(std::cin, targetPath);
                cv::Mat target = cv::imread(targetPath, cv::IMREAD_GRAYSCALE);
                if (target.empty()) {
                    std::cerr << "Could not read the target image.\n";
                    break;
                }
                cv::Mat matched = ImageProcessor::matchHistogram(gray, target);
                cv::imshow("Histogram Matched", matched);
                cv::waitKey(0);
                break;
            }
            case 4: {
                cv::Mat inverted = PixelOperations::invert(gray);
                cv::imshow("Inverted Image", inverted);
                cv::waitKey(0);
                break;
            }
            case 5: {
                const std::string win = "Gaussian Blur";
                int kSize = 5;

                cv::namedWindow(win, cv::WINDOW_AUTOSIZE);
                cv::createTrackbar("Kernel size", win, &kSize, 31, [](int pos, void* userdata) {
                    int k = pos;
                    if (k % 2 == 0) k += 1; // deve essere dispari
                    if (k < 1) k = 1;
                    const cv::Mat& img = *static_cast<cv::Mat*>(userdata);
                    cv::Mat blurred = Filters::blur(img, k);
                    cv::imshow("Gaussian Blur", blurred);
                }, &gray);

                cv::setTrackbarPos("Kernel size", win, 5);
                cv::waitKey(0);
                break;
            }
            case 6: {
                const std::string win = "Sobel Filter";
                int dummy = 1;

                cv::namedWindow(win, cv::WINDOW_AUTOSIZE);
                cv::createTrackbar("Apply", win, &dummy, 1, [](int pos, void* userdata) {
                    if (pos == 0) return;
                    const cv::Mat& img = *static_cast<cv::Mat*>(userdata);
                    cv::Mat sobel = Filters::sobel(img);
                    cv::imshow("Sobel Filter", sobel);
                }, &gray);

                cv::setTrackbarPos("Apply", win, 1);
                cv::waitKey(0);
                break;
            }

            case 7: {
                const std::string win = "Roberts Filter";
                int dummy = 1;

                cv::namedWindow(win, cv::WINDOW_AUTOSIZE);
                cv::createTrackbar("Apply", win, &dummy, 1, [](int pos, void* userdata) {
                    if (pos == 0) return;
                    const cv::Mat& img = *static_cast<cv::Mat*>(userdata);
                    cv::Mat roberts = Filters::roberts(img);
                    cv::imshow("Roberts Filter", roberts);
                }, &gray);
                cv::setTrackbarPos("Apply", win, 1);
                cv::waitKey(0);
                break;
            }

            // FIXME: fix dell'invocazione del meotodo alla chiamata per la funzione dello sharp
            case 8: {
                const std::string win = "Sharpening with laplacian";
                int mode = 0;

                cv::namedWindow(win, cv::WINDOW_AUTOSIZE);
                cv::createTrackbar("Mode (0: -1, 1: +1)", win, &mode, 1, [](int pos, void* userdata) {
                    const cv::Mat& gray = *static_cast<cv::Mat*>(userdata);
                    int c = (pos == 0) ? -1 : 1;
                    cv::Mat sharpened = Filters::sharpenLaplacian(gray, c);
                    cv::imshow("Sharpening (Laplacian Theory)", sharpened);
                }, &gray);

                cv::setTrackbarPos("Mode (0: -1, 1: +1)", win, 0);
                cv::waitKey(0);
                break;
            }

            default:
                std::cerr << "Invalid choice.\n";
        }
    }
}
