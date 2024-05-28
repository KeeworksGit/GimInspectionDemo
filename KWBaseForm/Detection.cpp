#include "pch.h"
#include "Detection.h";

Mat loadImageFromUnsignedCharArray(const unsigned char* imageData, int width, int height, int channels) {
	// ���ο� Mat ��ü ����
	Mat image(height, width, CV_8UC(channels));

	// �̹��� ������ ����
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			for (int c = 0; c < channels; ++c) {
				// �Է� �����Ͱ� RGB�� ���, ������ BGR�� �����Ͽ� ����
				int index = (y * width + x) * channels + c;
				if (channels == 3) {
					// RGB �����͸� BGR�� �����Ͽ� ����
					if (c == 0)
						image.at<Vec3b>(y, x)[2] = imageData[index];  // R -> B
					else if (c == 1)
						image.at<Vec3b>(y, x)[1] = imageData[index];  // G -> G
					else if (c == 2)
						image.at<Vec3b>(y, x)[0] = imageData[index];  // B -> R
				}
				else if (channels == 1) {
					// Grayscale �̹����� ���, ä�� 0�� ���� �״�� ����
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
	// �簢�� �׸���
	rectangle(image, Point(x, y), Point(x + width, y + height), Scalar(0, 255, 0), 2);

	if (score > 0) {
		// ���ھ �ؽ�Ʈ�� ��ȯ
		std::string scoreText = "Score: " + std::to_string(score);

		// �ؽ�Ʈ�� �߰��� ��ġ ���� (�簢�� ���� ���)
		Point textPosition(x, y - 20); // ���ھ� �ؽ�Ʈ�� �簢�� ���� �ø��� ���� y - 20

		// �ؽ�Ʈ �߰�
		putText(image, scoreText, textPosition, FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
	}
}

void Detection::model_init(string model_path)
{
	trainedModelPath = model_path;
	/***********************************************************
*    1. �� ���� �� �˻� ��� �ڵ� ����,
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
	 *    2. �� ���� Ȯ�� (Optional)
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
	 *    3. �˻� �ɼ� Ȯ�� �� ���� (Optional)
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
			std::cerr << "�� ������ 3���� Ŭ������ ������ ���� ����մϴ�." << std::endl;
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
	 *    4. �̹��� �˻��ϱ�, Inspect images
	 *       �̹��� ������� ���ٰ� �����Ѵ�.
	 ***********************************************************/
	 /***********************************************************
	  *    4-1. Single Image Inference
	  ***********************************************************/
	unsigned char* ucImageData = nullptr;
	std::vector<long long> inferenceTimes;

	// �̹��� ������ �޸𸮸� �����մϴ�. (�����ϰ���)
	if (ucImageData != nullptr) {
		retval = SaigeFreeImageData(ucImageData);
		if (retval < 0) {
			std::cerr << "SaigeFreeImageData() Failed - " << SaigeStrError(retval) << std::endl;
		}
		ucImageData = nullptr;
	}

	// �̹��� �����͸� �ε��մϴ�.
	ucImageData = (unsigned char*)SaigeGetImageData(imagePath.c_str(), &w, &h, &c, &type);
	if (ucImageData == nullptr) {
		std::cerr << "SaigeGetImageData() failed - " << imagePath << std::endl;
	}
	/***********************************************************
	 *    4-1. �˻� �Լ� ȣ���ϱ�, Call Infer API
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
	 *    4-2. �˻� ��� �޾ƿ���, Retrieve inference results
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

	// Detection�� nObject�� ���� struct SaigeDetectedObject�� �޸𸮸� �Ҵ��ؾ��մϴ�.
// �� ���������� c++ vector�� �̿��ؼ� �޸� ������ ���� �����ʵ��� �մϴ�.
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

	// �̹��� mat���� ��ȯ -> �˻� ��� ǥ��
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