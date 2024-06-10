#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

class OverLapDetection {
public:
	static bool detect(Mat image, int threshold = 20, int part_num = 10, float* result = nullptr);
	static void test(Mat image);
};