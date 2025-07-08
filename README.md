# Low-Level Image Processing Toolkit

This project provides a simple C++ and OpenCV interface to perform **low-level spatial operations on images**.

It is intended for educational and demonstration purposes, offering a text GUI and some visual interaction via sliders (`cv::createTrackbar`).

## 🧠 Feature Description

### 1. 📊 Histogram
- Calculate and display the histogram of intensity levels.
- Implemented with `cv::calcHist` and custom drawing in OpenCV.

### 2. ⚖️ Equalize Histogram
- Improve contrast with `cv::equalizeHist()`.
- Useful for images with very dark or very light areas.

### 3. 🎯 Histogram Matching
- Compare and match the histogram of an image to that of a target image.
- Mapping based on cumulative distributions.

### 4. ⬛ Invert Image
- Per-pixel inversion: `255 - pixels`.
- Manually implemented (without using `bitwise_not`).

## 🔧 Filters and Edge Detection

### 5. 🌫 Gaussian Blur
- Apply smoothing with a Gaussian filter: `cv::GaussianBlur`.
- Dynamic control of the **kernel size** with an OpenCV slider.
- Only odd values ​​allowed (3, 5, 7...).

### 6. 🟦 Sobel
- Calculate the gradient in X and Y: `cv::Sobel`.
- Weighted sum of the two directions to highlight the edges.
- The image is converted to grayscale if necessary.

### 7. 🟪 Roberts
- Edge operator with 2×2 kernel (not directly available in OpenCV).
- Implemented with `cv::filter2D` and custom kernels:
- `[[1, 0], [0, -1]]` for main diagonal
- `[[0, 1], [-1, 0]]` for inverse diagonal

---

## ✨ Sharpening with Laplacian

### 8. 🔪 Sharpen Image (with Laplacian)

- The `c` value is dynamically selectable:
- `c = -1`: sharp effect (subtract Laplacian)
- `c = +1`: smooth effect (add Laplacian)
- Used `cv::Laplacian` + `cv::addWeighted`.

---

## 🖱 Graphical Interaction

- Dynamic filters (Gaussian, Sharpen) show **sliders (trackbars)** for real-time parameter control.
- Each slider changes the displayed image instantly.
- Window created with `cv::namedWindow` + `cv::imshow` + `cv::createTrackbar`.

---

## 🛠 Requirements

- OpenCV 4.x
- CMake
- C++17 compiler or higher
