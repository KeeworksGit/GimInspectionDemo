#pragma once
#include <limits.h>
#include <stdlib.h>

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <iostream>

#include "SaigeVisionAPI.h"
#include "SaigeVisionUtil.h"
#include "opencv2/opencv.hpp"


using namespace std;
using namespace cv;

struct DetectionResult {
	Mat image;
	int object_count = 0;
	int objectScoreThreshold = -1;
	int total_inference_time = 0;
};

class Detection {
public:
	string trainedModelPath = "./det_0528_1132_best.saigedet"; //example
	int retval;
	int verbosity = 3;
	int deviceIndex = 0;
	bool detailedTime = false;
	bool optimize = false;
	int waitkeyMilliSecond = 0;
	SaigeInferenceHandle handle = nullptr;
	SaigeHandleConfig config;
	unsigned int handleFlags = 0;
	SaigeInferenceResult result = nullptr;
	int h = 0, w = 0, c = 0, type = -1;
	int nbatch = 1;
	SaigeModelInfo* modelInfo;
	SaigeInferenceOption* options;

	bool show_score = true;

	void model_init(string model_path, int objectScoreThreshold);
	DetectionResult run_detection(string imagePath);
};