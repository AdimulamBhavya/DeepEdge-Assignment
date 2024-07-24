google.com, pub-8609731628866080, DIRECT, f08c47fec0942fa0

#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

void my_resize(const cv::Mat& src, cv::Mat& dst, cv::Size dsize, int interpolation)
{
    dst = cv::Mat(dsize, src.type());
    double scale_x = (double) dsize.width / src.cols;
    double scale_y = (double) dsize.height / src.rows;

    for (int y = 0; y < dsize.height; ++y) {
        for (int x = 0; x < dsize.width; ++x) {
            double src_x = x / scale_x;
            double src_y = y / scale_y;

            if (interpolation == cv::INTER_NEAREST) {
                int nearest_x = std::round(src_x);
                int nearest_y = std::round(src_y);
                dst.at<cv::Vec3b>(y, x) = src.at<cv::Vec3b>(nearest_y, nearest_x);
            } else if (interpolation == cv::INTER_LINEAR) {
                int x1 = std::floor(src_x);
                int x2 = std::min(x1 + 1, src.cols - 1);
                int y1 = std::floor(src_y);
                int y2 = std::min(y1 + 1, src.rows - 1);
                double a = src_x - x1;
                double b = src_y - y1;

                cv::Vec3b p1 = src.at<cv::Vec3b>(y1, x1);
                cv::Vec3b p2 = src.at<cv::Vec3b>(y1, x2);
                cv::Vec3b p3 = src.at<cv::Vec3b>(y2, x1);
                cv::Vec3b p4 = src.at<cv::Vec3b>(y2, x2);

                dst.at<cv::Vec3b>(y, x) = (1 - a) * (1 - b) * p1 + a * (1 - b) * p2 + (1 - a) * b * p3 + a * b * p4;
            } else if (interpolation == cv::INTER_CUBIC) {
                // For simplicity, we'll omit the cubic interpolation implementation here.
                // Implementing bicubic interpolation is quite complex and beyond the scope of this response.
                // Use OpenCV's implementation instead.
                std::cerr << "INTER_CUBIC not implemented." << std::endl;
                return;
            }
        }
    }
}

int main()
{
    cv::Mat image = cv::imread("G178_2-1080.BMP");

    cv::Size new_size(image.cols / 2, image.rows / 2);
    cv::Mat resized_image;

    // Measure timing and compare correctness
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        my_resize(image, resized_image, new_size, cv::INTER_NEAREST);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken for 1000 iterations using my_resize INTER_NEAREST: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        my_resize(image, resized_image, new_size, cv::INTER_LINEAR);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken for 1000 iterations using my_resize INTER_LINEAR: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    // Save the resized images for comparison
    cv::imwrite("my_resized_nearest.bmp", resized_image);
    my_resize(image, resized_image, new_size, cv::INTER_LINEAR);
    cv::imwrite("my_resized_linear.bmp", resized_image);

    return 0;
}
