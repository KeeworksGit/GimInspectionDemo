#include "pch.h"
#include "OverLapDetection.h"

// �̹����� RGB �� ä�ο� ����ġ�� �����Ͽ� ��⸦ ����ϴ� �Լ�
float calculateBrightness(const cv::Mat& image, float weightR, float weightG, float weightB) {
    // �̹����� 3ä��(BGR)���� Ȯ��
    if (image.channels() != 3) {
        // ���� ó��: �̹����� 3ä���� �ƴ� ���
        throw std::invalid_argument("Input image must have 3 channels (BGR).");
    }

    cv::Mat bgr[3]; // B, G, R ä���� ������ �迭

    // ä�� �и�
    cv::split(image, bgr);

    // �� ä�ο� ����ġ�� �����Ͽ� ��� ���
    float brightness = 0.0;
    brightness += cv::sum(bgr[0])[0] * weightB; // Blue ä��
    brightness += cv::sum(bgr[1])[0] * weightG; // Green ä��
    brightness += cv::sum(bgr[2])[0] * weightR; // Red ä��

    return brightness;
}

void calculateHistogram(const cv::Mat& image, cv::Mat& hist) {
    int histSize = 256;    // ��� ���� (0-255)
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true, accumulate = false;

    cv::calcHist(&image, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);
    cv::normalize(hist, hist, 0, 400, cv::NORM_MINMAX, -1, cv::Mat());
}

void calculateHistogramStatistics(const cv::Mat& hist, float& mean, float& stddev) {
    // ������׷��� ������ ����մϴ�.
    mean = 0.0;
    stddev = 0.0;
    int total_pixels = 0;

    // ������׷��� �� �ȼ� ���� ����մϴ�.
    for (int i = 0; i < hist.rows; i++) {
        total_pixels += hist.at<float>(i);
    }

    // ������׷��� ����� ����մϴ�.
    for (int i = 0; i < hist.rows; i++) {
        mean += i * hist.at<float>(i);
    }
    mean /= total_pixels;

    // ������׷��� �л��� ����մϴ�.
    for (int i = 0; i < hist.rows; i++) {
        stddev += (i - mean) * (i - mean) * hist.at<float>(i);
    }
    stddev = std::sqrt(stddev / total_pixels);
}

bool OverLapDetection::detect(Mat image, int threshold, int part_num, float* result)
{
    cv::Mat grayImage;
    if (image.channels() == 3) {
        // �÷� �̹����� ������� ��ȯ
        cv::cvtColor(image, grayImage, cv::COLOR_BGR2HLS);
        cv::cvtColor(grayImage, grayImage, cv::COLOR_BGR2GRAY);
        //cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    }
    else if (image.channels() == 1) {
        grayImage = image.clone(); // �̹� ��� �̹����� ��� �����Ͽ� ���
    }
    else {
        std::cerr << "�̹��� ä���� �ùٸ��� �ʽ��ϴ�!" << std::endl;
        return false;
    }

    // �̹����� n by n���� ���
    int partHeight = grayImage.rows / part_num;
    int partWidth = grayImage.cols / part_num;

    for (int i = 0; i < part_num; ++i) {
        for (int j = 0; j < part_num; ++j) {
            // �κ� �̹����� ���� ��ġ ���
            int startY = i * partHeight;
            int startX = j * partWidth;

            // �κ� �̹����� �� ��ġ ���
            int endY = (i + 1) * partHeight;
            int endX = (j + 1) * partWidth;

            // ������ ��� ���� ���� ũ�⸸ŭ�� ���
            if (i == part_num - 1) {
                endY = grayImage.rows;
            }
            if (j == part_num - 1) {
                endX = grayImage.cols;
            }

            // �κ� �̹��� ����
            cv::Mat partImage = grayImage(cv::Range(startY, endY), cv::Range(startX, endX));

            // ������׷� ���
            cv::Mat hist;
            calculateHistogram(partImage, hist);

            // ������׷� ��跮 ���
            float mean, stddev;
            calculateHistogramStatistics(hist, mean, stddev);

            // ��� ���
            //std::cout << "�κ� (" << i << "," << j << "): ";
            //std::cout << "���: " << mean << ", ǥ�� ����: " << stddev << std::endl;
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
    // �� ä�ο� ���� ����ġ
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
