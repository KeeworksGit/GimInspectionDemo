#include "pch.h"
#include "OverLapDetection.h"

// 이미지의 RGB 각 채널에 가중치를 적용하여 밝기를 계산하는 함수
float calculateBrightness(const cv::Mat& image, float weightR, float weightG, float weightB) {
    // 이미지가 3채널(BGR)인지 확인
    if (image.channels() != 3) {
        // 예외 처리: 이미지가 3채널이 아닌 경우
        throw std::invalid_argument("Input image must have 3 channels (BGR).");
    }

    cv::Mat bgr[3]; // B, G, R 채널을 저장할 배열

    // 채널 분리
    cv::split(image, bgr);

    // 각 채널에 가중치를 적용하여 밝기 계산
    float brightness = 0.0;
    brightness += cv::sum(bgr[0])[0] * weightB; // Blue 채널
    brightness += cv::sum(bgr[1])[0] * weightG; // Green 채널
    brightness += cv::sum(bgr[2])[0] * weightR; // Red 채널

    return brightness;
}

void calculateHistogram(const cv::Mat& image, cv::Mat& hist) {
    int histSize = 256;    // 밝기 레벨 (0-255)
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true, accumulate = false;

    cv::calcHist(&image, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);
    cv::normalize(hist, hist, 0, 400, cv::NORM_MINMAX, -1, cv::Mat());
}

void calculateHistogramStatistics(const cv::Mat& hist, float& mean, float& stddev) {
    // 히스토그램의 분포를 계산합니다.
    mean = 0.0;
    stddev = 0.0;
    int total_pixels = 0;

    // 히스토그램의 총 픽셀 수를 계산합니다.
    for (int i = 0; i < hist.rows; i++) {
        total_pixels += hist.at<float>(i);
    }

    // 히스토그램의 평균을 계산합니다.
    for (int i = 0; i < hist.rows; i++) {
        mean += i * hist.at<float>(i);
    }
    mean /= total_pixels;

    // 히스토그램의 분산을 계산합니다.
    for (int i = 0; i < hist.rows; i++) {
        stddev += (i - mean) * (i - mean) * hist.at<float>(i);
    }
    stddev = std::sqrt(stddev / total_pixels);
}

bool OverLapDetection::detect(Mat image, int threshold, int part_num, float* result)
{
    cv::Mat grayImage;
    if (image.channels() == 3) {
        // 컬러 이미지를 흑백으로 변환
        cv::cvtColor(image, grayImage, cv::COLOR_BGR2HLS);
        cv::cvtColor(grayImage, grayImage, cv::COLOR_BGR2GRAY);
        //cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    }
    else if (image.channels() == 1) {
        grayImage = image.clone(); // 이미 흑백 이미지인 경우 복사하여 사용
    }
    else {
        std::cerr << "이미지 채널이 올바르지 않습니다!" << std::endl;
        return false;
    }

    // 이미지를 n by n으로 등분
    int partHeight = grayImage.rows / part_num;
    int partWidth = grayImage.cols / part_num;

    for (int i = 0; i < part_num; ++i) {
        for (int j = 0; j < part_num; ++j) {
            // 부분 이미지의 시작 위치 계산
            int startY = i * partHeight;
            int startX = j * partWidth;

            // 부분 이미지의 끝 위치 계산
            int endY = (i + 1) * partHeight;
            int endX = (j + 1) * partWidth;

            // 마지막 행과 열은 남은 크기만큼만 사용
            if (i == part_num - 1) {
                endY = grayImage.rows;
            }
            if (j == part_num - 1) {
                endX = grayImage.cols;
            }

            // 부분 이미지 생성
            cv::Mat partImage = grayImage(cv::Range(startY, endY), cv::Range(startX, endX));

            // 히스토그램 계산
            cv::Mat hist;
            calculateHistogram(partImage, hist);

            // 히스토그램 통계량 계산
            float mean, stddev;
            calculateHistogramStatistics(hist, mean, stddev);

            // 결과 출력
            //std::cout << "부분 (" << i << "," << j << "): ";
            //std::cout << "평균: " << mean << ", 표준 편차: " << stddev << std::endl;
            //imshow("asd", partImage);
            //waitKey(0);
            
            if (result) {
                *result += mean;
            }
            if (mean < threshold) {
                return true;
            }
        }
    }
    std::cout << std::endl;
    return false;
}

void OverLapDetection::test(Mat image)
{
    // 각 채널에 대한 가중치
    float weightR = 0.5; // Red
    float weightG = 0.5; // Green
    float weightB = 0.5; // Blue
    float brightness = calculateBrightness(image, weightR, weightG, weightB);
    std::cout << "Brightness1: " << brightness << std::endl;


    weightR = 1.1; // Red
    weightG = 0.3; // Green
    weightB = 0.1; // Blue
    brightness = calculateBrightness(image, weightR, weightG, weightB);
    std::cout << "Brightness2: " << brightness << std::endl;
    return;
}
