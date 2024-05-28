#include "pch.h"
#include "Detection.h";

Mat loadImageFromUnsignedCharArray(const unsigned char* imageData, int width, int height, int channels) {
	// 새로운 Mat 객체 생성
	Mat image(height, width, CV_8UC(channels));

	// 이미지 데이터 복사
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			for (int c = 0; c < channels; ++c) {
				// 입력 데이터가 RGB인 경우, 순서를 BGR로 변경하여 저장
				int index = (y * width + x) * channels + c;
				if (channels == 3) {
					// RGB 데이터를 BGR로 변경하여 저장
					if (c == 0)
						image.at<Vec3b>(y, x)[2] = imageData[index];  // R -> B
					else if (c == 1)
						image.at<Vec3b>(y, x)[1] = imageData[index];  // G -> G
					else if (c == 2)
						image.at<Vec3b>(y, x)[0] = imageData[index];  // B -> R
				}
				else if (channels == 1) {
					// Grayscale 이미지인 경우, 채널 0의 값을 그대로 저장
					image.at<Vec3b>(y, x)[0] = imageData[index];
					image.at<Vec3b>(y, x)[1] = imageData[index];
					image.at<Vec3b>(y, x)[2] = imageData[index];
				}
			}
		}
	}

	return image;
}


void drawRectangleOnImage(Mat& image, int x, int y, int width, int height, int score = 0) {
	// 사각형 그리기
	rectangle(image, Point(x, y), Point(x + width, y + height), Scalar(0, 255, 0), 2);

	if (score > 0) {
		// 스코어를 텍스트로 변환
		std::string scoreText = "Score: " + std::to_string(score);

		// 텍스트를 추가할 위치 설정 (사각형 왼쪽 상단)
		Point textPosition(x, y - 20); // 스코어 텍스트를 사각형 위로 올리기 위해 y - 20

		// 텍스트 추가
		putText(image, scoreText, textPosition, FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
	}
}

void Detection::model_init(string model_path)
{
	trainedModelPath = model_path;
	/***********************************************************
*    1. 모델 파일 및 검사 결과 핸들 생성,
*       Create handles for model files and inference results
***********************************************************/
	if (optimize) {
		handleFlags |= SAIGE_OPTIMIZE_HANDLE;
	}
	retval = SaigeCreateInferenceHandle(&handle, kProjectTypeDET, trainedModelPath.c_str(),
		deviceIndex, &config, handleFlags);
	if (retval < 0) {
		std::cerr << "SaigeCreateInferenceHandle failed - " << SaigeStrError(retval) << std::endl;
	}

	retval = SaigeCreateInferenceResult(&result);
	if (retval < 0) {
		std::cerr << "SaigeCreateInferenceResult failed - " << SaigeStrError(retval) << std::endl;
		SaigeDestroyInferenceHandle(handle);
	}

	/***********************************************************
	 *    2. 모델 정보 확인 (Optional)
	 *       Check model information
	 ***********************************************************/
	std::cout << SaigeGetModuleVersion() << std::endl;
	modelInfo = new SaigeModelInfo;
	retval = SaigeGetModelInfo(handle, modelInfo);
	if (retval < 0) {
		std::cerr << "SaigeGetModelInfo() failed - " << SaigeStrError(retval) << std::endl;
	}
	else if (verbosity >= 1) {
		std::cout << "[Object Detection Model Info]" << std::endl;
		std::cout << "Network Type: " << modelInfo->networkType << std::endl;
		std::cout << "TrainingTimeStarted: " << modelInfo->trainingTimeStarted << std::endl;
		std::cout << "TrainingTimeCompleted: " << modelInfo->trainingTimeCompleted << std::endl;
		std::cout << "TrainingTimeElapsed: " << modelInfo->trainingTimeElapsed << std::endl;
		std::cout << "UsedGpuName: " << modelInfo->usedGpuName << std::endl;
		std::cout << "Number of Train Images: " << modelInfo->numOfTrainImages << std::endl;
		std::cout << "Number of Validation Images: " << modelInfo->numOfValidationImages
			<< std::endl;
		std::cout << "Number of Iterations: " << modelInfo->numOfIterations << std::endl;
		std::cout << "Number of Classes: " << modelInfo->numOfClasses << std::endl;
		for (auto i = 0; i < modelInfo->numOfClasses; ++i) {
			uint8_t red, green, blue;
			SaigeColorCodeToRGB(modelInfo->classColors[i], &red, &green, &blue);
			std::cout << modelInfo->classNames[i] << ": color RGB(" << (int)red << ", " << (int)green
				<< ", " << (int)blue << ") - " << (modelInfo->classIsNg[i] ? "NG" : "OK")
				<< std::endl;
		}
		std::cout << std::endl << std::endl;
	}

	/***********************************************************
	 *    3. 검사 옵션 확인 및 수정 (Optional)
	 *       Check inference options and set new values
	 ***********************************************************/
	 // objectScoreThresholdPerClass[numOfClasses]
	 // objectAreaThresholdPerClass[numOfClasses]
	 // maxNumOfDetectedObjects[numOfClasses]
	options = new SaigeInferenceOption;
	options->objectScoreThresholdPerClass[0] = 80;
	options->objectScoreThresholdPerClass[1] = 80;
	options->objectScoreThresholdPerClass[2] = 80;

	options->objectAreaThresholdPerClass[0] = 0;
	options->objectAreaThresholdPerClass[1] = 0;
	options->objectAreaThresholdPerClass[2] = 0;

	options->maxNumOfDetectedObjects[0] = -1;
	options->maxNumOfDetectedObjects[1] = -1;
	options->maxNumOfDetectedObjects[2] = -1;

	retval = SaigeSetInferenceOption(handle, options,
		SAIGE_SET_MAX_NUM_OF_DETECTED_OBJECTS |
		SAIGE_SET_OBJECT_SCORE_THRESHOLD |
		SAIGE_SET_OBJECT_AREA_THRESHOLD);
	if (retval < 0) {
		std::cerr << "SaigeSetInferenceOption() failed - " << SaigeStrError(retval) << std::endl;
		if (modelInfo->numOfClasses != 3) {
			std::cerr << "이 예제는 3개의 클래스를 가지는 모델을 사용합니다." << std::endl;
		}
		SaigeDestroyInferenceHandle(handle);
		SaigeDestroyInferenceResult(result);
	}

	retval = SaigeGetInferenceOption(handle, options);
	if (retval < 0) {
		std::cerr << "SaigeGetInferenceOption() failed - " << SaigeStrError(retval) << std::endl;
		SaigeDestroyInferenceHandle(handle);
		SaigeDestroyInferenceResult(result);
	}
	if (verbosity >= 1) {
		std::cout << "[Object Detection Inference Options]" << std::endl;
		std::cout << "Object Score Thresholds: (" << options->objectScoreThresholdPerClass[0];
		for (int i = 1; i < modelInfo->numOfClasses; ++i) {
			std::cout << ", " << options->objectScoreThresholdPerClass[i];
		}
		std::cout << ")" << std::endl;
		std::cout << "Object Area Thresholds: (" << options->objectAreaThresholdPerClass[0];
		for (int i = 1; i < modelInfo->numOfClasses; ++i) {
			std::cout << ", " << options->objectAreaThresholdPerClass[i];
		}
		std::cout << ")" << std::endl;
		std::cout << "Max Number of Detected Objects: (" << options->maxNumOfDetectedObjects[0];
		for (int i = 1; i < modelInfo->numOfClasses; ++i) {
			std::cout << ", " << options->maxNumOfDetectedObjects[i];
		}
		std::cout << ")" << std::endl;
	}
}

Mat Detection::run_detection(string imagePath)
{
	/***********************************************************
	 *    4. 이미지 검사하기, Inspect images
	 *       이미지 사이즈는 같다고 가정한다.
	 ***********************************************************/
	 /***********************************************************
	  *    4-1. Single Image Inference
	  ***********************************************************/
	unsigned char* ucImageData = nullptr;
	std::vector<long long> inferenceTimes;

	// 이미지 데이터 메모리를 해제합니다. (루프일관성)
	if (ucImageData != nullptr) {
		retval = SaigeFreeImageData(ucImageData);
		if (retval < 0) {
			std::cerr << "SaigeFreeImageData() Failed - " << SaigeStrError(retval) << std::endl;
		}
		ucImageData = nullptr;
	}

	// 이미지 데이터를 로드합니다.
	ucImageData = (unsigned char*)SaigeGetImageData(imagePath.c_str(), &w, &h, &c, &type);
	if (ucImageData == nullptr) {
		std::cerr << "SaigeGetImageData() failed - " << imagePath << std::endl;
	}
	/***********************************************************
	 *    4-1. 검사 함수 호출하기, Call Infer API
	 ***********************************************************/
	if (verbosity >= 2) {
		std::cout << "\n================================" << std::endl;
		std::cout << "(Start): Infer From Image: " << imagePath.c_str() << std::endl;
		std::cout << "---" << std::endl;
	}
	unsigned int imageFlag = SaigeConvertImageType(c, type);
	retval = SaigeInferFromByteArray(handle, ucImageData, w, h, imageFlag, result);
	if (retval < 0) {
		std::cerr << "SaigeInferFromByteArray() failed - " << SaigeStrError(retval)
			<< std::endl;
	}
	/***********************************************************
	 *    4-2. 검사 결과 받아오기, Retrieve inference results
	 ***********************************************************/
	int nObject;
	long long imreadTime, inferenceTime, postProcessingTime;
	retval = SaigeGetInferenceResultNumOfDetectedObjects(result, &nObject);
	if (retval < 0) {
		std::cerr << "SaigeGetInferenceResultNumOfDetectedObjects() failed - "
			<< SaigeStrError(retval) << std::endl;
		SaigeDestroyInferenceHandle(handle);
		SaigeDestroyInferenceResult(result);
	}

	// Detection은 nObject에 따라 struct SaigeDetectedObject의 메모리를 할당해야합니다.
// 본 예제에서는 c++ vector를 이용해서 메모리 해제를 따로 하지않도록 합니다.
	std::vector<SaigeDetectedObject> objects;
	objects.resize(nObject);

	retval = SaigeGetInferenceResultDetectedObjects(result, objects.data());
	if (retval < 0) {
		std::cerr << "SaigeGetInferenceResultDetectedObjects() failed - "
			<< SaigeStrError(retval) << std::endl;
		SaigeDestroyInferenceHandle(handle);
		SaigeDestroyInferenceResult(result);
	}

	retval = SaigeGetInferenceResultInspectionTime(result, &imreadTime, &inferenceTime,
		&postProcessingTime);
	if (retval < 0) {
		std::cerr << "SaigeGetInferenceResultInspectionTime() failed - "
			<< SaigeStrError(retval) << std::endl;
		SaigeDestroyInferenceHandle(handle);
		SaigeDestroyInferenceResult(result);
	}
	inferenceTimes.push_back(inferenceTime);


	// Display and Draw
	if (verbosity >= 2) {
		for (int i_box = 0; i_box < nObject; ++i_box) {
			std::cout << "[Detected Object " << i_box << "]" << std::endl;
			std::cout << "  - Class: " << modelInfo->classNames[objects[i_box].classIndex]
				<< std::endl;
			std::cout << "  - Box Coordinates (xywh): (" << objects[i_box].boundingBox.points[0]
				<< ", " << objects[i_box].boundingBox.points[1] << ", "
				<< objects[i_box].boundingBox.width << ", "
				<< objects[i_box].boundingBox.height << ")" << std::endl;
			std::cout << "  - Score: " << objects[i_box].score << std::endl;
			std::cout << "  - Area: " << objects[i_box].area << std::endl;
		}
		std::cout << "---\n(End) Inspection Time: " << inferenceTime << " ms" << std::endl;
	}

	// 이미지 mat으로 변환 -> 검사 결과 표시
	Mat result_image;
	if (nObject > 0) {
		result_image = loadImageFromUnsignedCharArray(ucImageData, w, h, c);

		// draw rectangle
		for (int i_box = 0; i_box < nObject; ++i_box) {
			if (show_score) {
				drawRectangleOnImage(
					result_image,
					objects[i_box].boundingBox.points[0],
					objects[i_box].boundingBox.points[1],
					objects[i_box].boundingBox.width,
					objects[i_box].boundingBox.height,
					objects[i_box].score
				);
			}
			else {
				drawRectangleOnImage(
					result_image,
					objects[i_box].boundingBox.points[0],
					objects[i_box].boundingBox.points[1],
					objects[i_box].boundingBox.width,
					objects[i_box].boundingBox.height
				);
			}
		}
		//resize(result_image, result_image, Size(1200, 800));
		//imshow("Loaded Image", result_image);
		//waitKey(0);
	}
	int64_t total = 0;
	for (auto time : inferenceTimes) {
		total += time;
	}
	if (verbosity >= 2) {
		std::cout << "Total time to infer with single images: " << total << " ms" << std::endl;
	}

	if (ucImageData != nullptr) {
		retval = SaigeFreeImageData(ucImageData);
		if (retval < 0) {
			std::cerr << "SaigeFreeImageData() Failed - " << SaigeStrError(retval) << std::endl;
		}
		ucImageData = nullptr;
	}
	return result_image;
}