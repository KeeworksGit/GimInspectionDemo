#pragma once
#include <Mil.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

#include <iostream>
#include <Windows.h>
#include <time.h>

#define GRAB_NUM 100 // Grab Buffer Size

using namespace std;
using namespace cv;
class CMil
{


public:
	CMil();
	~CMil();

	typedef struct
	{
		// Object
		MIL_ID MilDigit;
		MIL_ID MilDisp;

		// Buffer
		MIL_ID MilDispBuf_M;
		MIL_ID MilDispBuf_C;
		MIL_ID MilGrabBuf[GRAB_NUM];
		int UsedGrabBufSize = 0;
		
		// Image Format Feature
		MIL_INT SizeX;
		MIL_INT SizeY;
		MIL_INT SizeBit;
		MIL_INT64 OffsetX;
		MIL_INT64 OffsetY;		
		MIL_STRING PixelFormat;

		// Camera Control Feature
		MIL_DOUBLE AcquisitionFrameRate;
		MIL_DOUBLE ExposureTime;
		MIL_DOUBLE Gain;

		MIL_ID BufParent;
		MIL_ID* BufChild;
		MIL_ID MilImage1;


		// Grab Object
		MIL_ID ModifiedBufferId;
		MIL_INT ProcessedImageCount;

		Mat GrabImage;

		Mat MatOddImage;
		Mat MatEvenImage;
		MIL_ID OddImage;
		MIL_ID EvenImage;
		bool imgSaved;

	}HookDataStruct;

	HookDataStruct CAM1; // Camera DEV0
	HookDataStruct CAM2; // Camera DEV0
	HookDataStruct CAM3; // Camera DEV0
	HookDataStruct CAM4; // Camera DEV0
	
	// Custom Functions
	bool Allocation(int option); // 0 : Default | 1 : CXP | 2 : RADIENT | 3 : GIGE | 4  : USB3 | 5 : SOLIOS
	void Alloc_Buffer(); // Allocation Buffer
	void GrabProcess_Line2();
	void Alloc_MIL_ImageBuffer();
	void Re_Alloc_Buffer();

	static const int Total_Frame_Num_cpp = 8;

	MIL_ID MilApp;
	MIL_ID MilSystem;
	MIL_ID MilImageDigit;
	MIL_ID MilImageDisp;
	MIL_ID MilZoomDisp;

	MIL_ID OddImage;
	MIL_ID EvenImage;

	int SizeGimX;
	int SizeGimY;
	 
	MIL_ID OddImageAI;
	MIL_ID EvenImageAI;
	MIL_ID OddImageRule;
	MIL_ID EvenImageRule;
	MIL_ID ZoomImage;

	MIL_INT SizeBand1;

	MIL_ID OddImageDisplay;
	MIL_ID EvenImageDisplay;
	MIL_ID OddDisplayAI;
	MIL_ID EvenDisplayAI;
	MIL_ID OddDisplayRule;
	MIL_ID EvenDisplayRule;

	// HookFunction
	static MIL_INT MFTYPE ProcessingFunction2(MIL_INT HookType, MIL_ID HookId, void* HookDataPtr);
};

