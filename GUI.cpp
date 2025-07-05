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

    cv::Mat img = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Could not read the image: " << imagePath << std::endl;
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
        std::cout << "5) Blur Image\n";
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
                std::cin.ignore(); // clean up newline
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
                cv::Mat blurred = Filters::blur(gray, 5);
                cv::imshow("Blurred Image", blurred);
                cv::waitKey(0);
                break;
            }
            default:
                std::cerr << "Invalid choice.\n";
        }
    }
}
