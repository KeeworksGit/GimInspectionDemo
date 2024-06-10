#include "pch.h"
#include "CMil.h"

CMil::CMil() // 생성자
{

}

CMil::~CMil()
{

}

bool CMil::Allocation(int option)
{
	switch (option)
	{
	case 0:
		/* Allocate defaults. */
		MappAllocDefault(M_DEFAULT, &MilApp, &MilSystem, M_NULL, &CAM1.MilDigit, M_NULL);

		if (CAM1.MilDigit != NULL)
		{
			cout << ">>. Allocation Step Success. " << endl;

			Alloc_Buffer();

			return true;
		}
		else {
			cout << ">>. Allocation Step Fail. " << endl;
			return false;
		}
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

void CMil::Alloc_Buffer()
{

	CAM1.ProcessedImageCount = 0;

	MdigInquire(CAM1.MilDigit, M_SIZE_X, &CAM1.SizeX);
	MdigInquire(CAM1.MilDigit, M_SIZE_Y, &CAM1.SizeY);
	MdigInquire(CAM1.MilDigit, M_SIZE_BIT, &CAM1.SizeBit);
	MdigInquire(CAM1.MilDigit, M_SIZE_BAND, &SizeBand1);
	//겹침 검사시 back light 비추는 부분만 봐야해서 환경 맞춰서 자름
	CAM1.SizeX -= 390;

	cout << CAM1.SizeX << endl;
	cout << CAM1.SizeY << endl;
	cout << CAM1.SizeBit << endl;
	cout << SizeBand1 << endl;

	CAM1.BufChild = new MIL_ID[Total_Frame_Num_cpp];
	CAM1.GrabImage.create(CAM1.SizeY * Total_Frame_Num_cpp, CAM1.SizeX, CV_8UC3);

	//for (int i = 0; i < GRAB_NUM; i++)
	//{
	//	MbufAllocColor(MilSystem, SizeBand1, CAM1.SizeX, CAM1.SizeY, CAM1.SizeBit + M_UNSIGNED, M_IMAGE + M_GRAB + M_DISP, CAM1.MilGrabBuf + i);
	//	MbufClear(CAM1.MilGrabBuf[i], 0);
	//}

	for (CAM1.UsedGrabBufSize = 0; CAM1.UsedGrabBufSize < GRAB_NUM; CAM1.UsedGrabBufSize++)
	{
		MbufAllocColor(MilSystem, SizeBand1, CAM1.SizeX, CAM1.SizeY, CAM1.SizeBit + M_UNSIGNED, M_IMAGE + M_GRAB + M_DISP, CAM1.MilGrabBuf + CAM1.UsedGrabBufSize);
		MbufClear(CAM1.MilGrabBuf[CAM1.UsedGrabBufSize], 0);
	}

	MbufAllocColor(MilSystem, 3, CAM1.SizeX, CAM1.SizeY * (Total_Frame_Num_cpp), CAM1.SizeBit + M_UNSIGNED, M_IMAGE + M_GRAB + M_DISP, &CAM1.BufParent);

	for (int i = 0; i < Total_Frame_Num_cpp; i++)
	{
		MbufChild2d(CAM1.BufParent, 0, CAM1.SizeY * i, CAM1.SizeX, CAM1.SizeY, CAM1.BufChild + i);
		MbufClear(CAM1.BufChild[i], 0);
	}
}

void CMil::Re_Alloc_Buffer()
{
	MdigProcess(CAM1.MilDigit, CAM1.MilGrabBuf, GRAB_NUM, M_STOP, M_DEFAULT,
		reinterpret_cast<MIL_DIG_HOOK_FUNCTION_PTR>(ProcessingFunction2), &CAM1);

	while (CAM1.UsedGrabBufSize > 0)
		MbufFree(CAM1.MilGrabBuf[--CAM1.UsedGrabBufSize]);

	for (CAM1.UsedGrabBufSize = 0; CAM1.UsedGrabBufSize < GRAB_NUM; CAM1.UsedGrabBufSize++)
	{
		MbufAllocColor(MilSystem, SizeBand1, CAM1.SizeX, CAM1.SizeY, CAM1.SizeBit + M_UNSIGNED, M_IMAGE + M_GRAB + M_DISP, CAM1.MilGrabBuf + CAM1.UsedGrabBufSize);
		MbufClear(CAM1.MilGrabBuf[CAM1.UsedGrabBufSize], 0);
	}
}

void CMil::GrabProcess_Line2()
{
	cout << "GrabProcess_Line2" << endl;
	
	//seonhyo
	if (CAM1.UsedGrabBufSize > 0) {
		Re_Alloc_Buffer();
	}

	MdigProcess(CAM1.MilDigit, CAM1.MilGrabBuf, GRAB_NUM, M_SEQUENCE + M_COUNT(Total_Frame_Num_cpp), M_ASYNCHRONOUS, ProcessingFunction2, &CAM1);
}

MIL_INT MFTYPE CMil::ProcessingFunction2(MIL_INT HookType, MIL_ID HookId, void* HookDataPtr) {
	HookDataStruct* UserHookDataPtr = (HookDataStruct*)HookDataPtr;
	MIL_ID ModifiedBufferId;

	MdigGetHookInfo(HookId, M_MODIFIED_BUFFER + M_BUFFER_ID, &ModifiedBufferId); // Image Buffer

	MbufCopy(ModifiedBufferId, UserHookDataPtr->BufChild[UserHookDataPtr->ProcessedImageCount]);
	
	UserHookDataPtr->ProcessedImageCount++;
	//cout << UserHookDataPtr->ProcessedImageCount << endl;
	cout << "ProcessingFunction2      "<< UserHookDataPtr->ProcessedImageCount << endl;
	if (UserHookDataPtr->ProcessedImageCount == Total_Frame_Num_cpp)
	{
		// MbufSave(MIL_TEXT(".\\Image\\Origin.bmp"), UserHookDataPtr->BufParent);
		MbufGetColor2d(UserHookDataPtr->BufParent, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, UserHookDataPtr->SizeX, UserHookDataPtr->SizeY * Total_Frame_Num_cpp,(void*)(UserHookDataPtr->GrabImage.data));
		cout << "get Origin Image      "  << endl;
		UserHookDataPtr->ProcessedImageCount = 0;
		UserHookDataPtr->imgSaved = true;
	}
	return 0;
}


void CMil::Alloc_MIL_ImageBuffer()
{

	/*MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &OddImageDisplay);
	MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &EvenImageDisplay);*/

	MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &EvenDisplayAI);
	MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &OddDisplayRule);
	MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &EvenDisplayRule);
	MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilZoomDisp);

	/*MbufAllocColor(MilSystem, 3, CAM1.SizeX, (CAM1.SizeY * Total_Frame_Num_cpp) / 2, 8 + M_UNSIGNED, M_IMAGE + M_DISP, &OddImage);
	MbufAllocColor(MilSystem, 3, CAM1.SizeX, (CAM1.SizeY * Total_Frame_Num_cpp) / 2 , 8 + M_UNSIGNED, M_IMAGE + M_DISP, &EvenImage);*/

	MbufAllocColor(MilSystem, 3, CAM1.SizeX, CAM1.SizeY * Total_Frame_Num_cpp / 2, 8 + M_UNSIGNED, M_IMAGE + M_DISP, &EvenImageAI);
	MbufAllocColor(MilSystem, 3, CAM1.SizeX, CAM1.SizeY * Total_Frame_Num_cpp / 2, 8 + M_UNSIGNED, M_IMAGE + M_DISP, &OddImageRule);
	MbufAllocColor(MilSystem, 3, CAM1.SizeX, CAM1.SizeY * Total_Frame_Num_cpp / 2, 8 + M_UNSIGNED, M_IMAGE + M_DISP, &EvenImageRule);
	MbufAllocColor(MilSystem, 3, CAM1.SizeX, CAM1.SizeY * Total_Frame_Num_cpp / 2, 8 + M_UNSIGNED, M_IMAGE + M_DISP, &ZoomImage);
	
	/*MdispControl(OddImageDisplay, M_FILL_DISPLAY, M_ENABLE);
	MdispControl(EvenImageDisplay, M_FILL_DISPLAY, M_ENABLE);*/

	MdispControl(EvenDisplayAI, M_FILL_DISPLAY, M_ENABLE);
	MdispControl(OddDisplayRule, M_FILL_DISPLAY, M_ENABLE);
	MdispControl(EvenDisplayRule, M_FILL_DISPLAY, M_ENABLE);
	MdispControl(MilZoomDisp, M_FILL_DISPLAY, M_ENABLE);
}
