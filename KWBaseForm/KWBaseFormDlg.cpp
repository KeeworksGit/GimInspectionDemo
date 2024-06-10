
// KWBaseFormDlg.cpp: 구현 파일
//


#include "pch.h"
#include "framework.h"
#include "KWBaseForm.h"
#include "KWBaseFormDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKWBaseFormDlg 대화 상자

CKWBaseFormDlg::CKWBaseFormDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KWBASEFORM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_KW_LOGO);
}

void CKWBaseFormDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DISP_0, m_CtrlDisp0);
	DDX_Control(pDX, IDC_DISP_1, m_CtrlDisp1);
	DDX_Control(pDX, IDC_DISP_2, m_CtrlDisp2);
	DDX_Control(pDX, IDC_DISP_3, m_CtrlDisp3);
	DDX_Control(pDX, IDC_DISP_5, m_CtrlDisp5);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ButtonSave);
	DDX_Control(pDX, IDC_BTN_INIT, m_ButtonInit);
	DDX_Control(pDX, IDC_BTN_TEST, m_ButtonTest);
	DDX_Control(pDX, IDC_EDIT1, Hole_Count);
	DDX_Control(pDX, IDC_EDIT2, Hole_MinSize);
	DDX_Control(pDX, IDC_EDIT3, EvenRuleDefactCount);
	DDX_Control(pDX, IDC_EDIT4, EvenRuleInspecTime);
	DDX_Control(pDX, IDC_EDIT5, EvenDL_Score);
	DDX_Control(pDX, IDC_EDIT6, Hole_Time);
	DDX_Control(pDX, IDC_EDIT7, EvenDL_Count);
	DDX_Control(pDX, IDC_EDIT8, EvenDL_Time);
	DDX_Control(pDX, IDC_EDIT9, Hole_Double);
	DDX_Control(pDX, IDC_BTN_ZOOM, m_btn_zoom);
	DDX_Control(pDX, IDC_LIST_LOG, m_ctrl_log);
	DDX_Control(pDX, IDC_BTN_ZOOM_RULE, m_btn_zoomrule);
	DDX_Control(pDX, IDC_BTN_ZOOM_HOLE, m_btn_zoomhole);

}

BEGIN_MESSAGE_MAP(CKWBaseFormDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_INIT, &CKWBaseFormDlg::OnBnClickedBtnInit)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CKWBaseFormDlg::OnBnClickedBtnSave)	
	ON_BN_CLICKED(IDC_BTN_ZOOM, &CKWBaseFormDlg::OnBnClickedBtnZoom)
	ON_BN_CLICKED(IDC_BTN_ZOOM_HOLE, &CKWBaseFormDlg::OnBnClickedBtnZoomHole)
	ON_BN_CLICKED(IDC_BTN_ZOOM_RULE, &CKWBaseFormDlg::OnBnClickedBtnZoomRule)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_INSPEC, &CKWBaseFormDlg::OnBnClickedBtnInspec)
	ON_BN_CLICKED(IDC_BTN_TEST, &CKWBaseFormDlg::OnBnClickedBtnTest)
END_MESSAGE_MAP()


// CKWBaseFormDlg 메시지 처리기
BOOL CKWBaseFormDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.

	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_ButtonSave.LoadBitmaps(IDB_StartBtn3);
	//m_ButtonInit.LoadBitmaps(IDB_InitBtn2);
	//m_ButtonTest.LoadBitmaps(IDB_TestBtn);
	m_btn_zoom.LoadBitmaps(IDB_BITMAP2);
	m_btn_zoomrule.LoadBitmaps(IDB_BITMAP2);
	m_btn_zoomhole.LoadBitmaps(IDB_BITMAP2);

	CRect buttonRect;
	CRect rect;
	GetWindowRect(&rect);
	int width = 1920;  // 새로운 너비
	int height = 1080; // 새로운 높이
	SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);

	SetWindowText(_T("Keeworks_Inspection_Module_V1.0"));

	//m_CtrlDisp0.SetWindowPos(NULL, 43, 159, 458, 391, SWP_NOSENDCHANGING); //odd
	//m_CtrlDisp1.SetWindowPos(NULL, 43, 600, 458, 391, SWP_NOSENDCHANGING); //even

	m_CtrlDisp5.SetWindowPos(NULL, 100, 174, 459, 389, SWP_NOSENDCHANGING); // 상부 - 딥러닝
	m_CtrlDisp2.SetWindowPos(NULL, 100, 611, 459, 389, SWP_NOSENDCHANGING); // 하부조명
	m_CtrlDisp3.SetWindowPos(NULL, 627, 174, 459, 389, SWP_NOSENDCHANGING); // 상부 - 규칙기반
	

	//m_ButtonInit.SetWindowPos(NULL, 988, 221, 259, 68, SWP_NOSENDCHANGING); // INIT 버튼
	//m_ButtonTest.SetWindowPos(NULL, 1268, 221, 259, 68, SWP_NOSENDCHANGING); // INIT 버튼
	m_ButtonSave.SetWindowPos(NULL, 1512, 190, 259, 68, SWP_NOSENDCHANGING); // 결과 저장 버튼

	

	m_btn_zoom.SetWindowPos(NULL, 531, 142, 24, 24, SWP_NOSENDCHANGING); // 이물 - 딥
	//1406, 583
	m_btn_zoomrule.SetWindowPos(NULL, 1058, 142, 24, 24, SWP_NOSENDCHANGING); // 이물 - 규칙
	m_btn_zoomhole.SetWindowPos(NULL, 531, 583, 24, 24, SWP_NOSENDCHANGING); // 하부

	EvenRuleInspecTime.SetWindowPos(NULL, 592, 735, 304, 43, SWP_NOSENDCHANGING); // 규칙기반 시간 -- HIDE



	EvenDL_Count.SetWindowPos(NULL, 1144, 206, 304, 43, SWP_NOSENDCHANGING); // 이물 개수 - 딥러닝
	EvenRuleDefactCount.SetWindowPos(NULL, 1144, 304, 304, 43, SWP_NOSENDCHANGING); // 이물 개수 - 규칙기반
	EvenDL_Time.SetWindowPos(NULL, 1144, 402, 304, 43, SWP_NOSENDCHANGING); // 딥러닝 검사 시간
	
	
	Hole_Count.SetWindowPos(NULL, 627, 643, 304, 43, SWP_NOSENDCHANGING); // 하부조명 구멍 개수
	Hole_Double.SetWindowPos(NULL, 627, 741, 304, 43, SWP_NOSENDCHANGING); // 겹침 여부
	Hole_Time.SetWindowPos(NULL, 627, 839, 304, 43, SWP_NOSENDCHANGING); // 하부 조명 검사 시간

	m_ctrl_log.SetWindowPos(NULL, 1144, 529, 628, 471, SWP_NOSENDCHANGING); // 프로그램 진행상황 로그창

	Hole_MinSize.SetWindowPos(NULL, 627, 651, 304, 43, SWP_NOSENDCHANGING); // 기준 구멍 넓이  --HIDE
	EvenDL_Score.SetWindowPos(NULL, 1467, 828, 304, 43, SWP_NOSENDCHANGING); // 점수 안보여줌  -- HIDE

	{ // 안쓰는 오브젝트 숨김
		m_ButtonInit.ShowWindow(SW_HIDE);
		m_ButtonInit.EnableWindow(FALSE);
		m_ButtonTest.ShowWindow(SW_HIDE);
		m_ButtonTest.EnableWindow(FALSE);
		EvenDL_Score.ShowWindow(SW_HIDE);
		EvenDL_Score.EnableWindow(FALSE);
		EvenRuleInspecTime.ShowWindow(SW_HIDE);
		EvenRuleInspecTime.EnableWindow(FALSE);
		Hole_MinSize.ShowWindow(SW_HIDE);
		Hole_MinSize.EnableWindow(FALSE);
	}
	// MIL 관련 초기화 
	// MIL로 띄울 이미지 odd, even buf할당
	
	// 최종 결과물을 가질 MIL_ID Rule 2개 AI 2개
	// 토탈 MIL_ID 이미지 버퍼 6개 할당

	//motor init
	motor.init();
	//model load init
	even_detection.model_init("./0607_1721_hsv_best.saigedet", 90);

	string result_message = "[성공] 장비 초기화가 완료 되었습니다!";
	cout << result_message << endl;
	str2log(&m_ctrl_log, result_message);
	AfxMessageBox(_T("김 생산라인 초기화가 완료 되었습니다."));





	//m_ButtonInit.EnableWindow(TRUE);
	//m_ButtonSave.EnableWindow(FALSE);

	ProcessInit();


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CKWBaseFormDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CKWBaseFormDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CDC MemDC;
		CBitmap bmp;
		CRect rct;
		this->GetClientRect(&rct);

		MemDC.CreateCompatibleDC(&dc);
		bmp.LoadBitmap(IDB_BG5);
		MemDC.SelectObject(&bmp);

		dc.BitBlt(0, 0, rct.Width(), rct.Height(), &MemDC, 0, 0, SRCCOPY);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CKWBaseFormDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CKWBaseFormDlg::ProcessInit()
{
	str2log(&m_ctrl_log, string("[진행] 카메라 초기화를 진행 중 입니다."));
	m_ctrl_log.SetTopIndex(m_ctrl_log.GetCount() - 1);
	m_classMil.Allocation(0);
	m_classMil.Alloc_MIL_ImageBuffer();

	MdispSelectWindow(m_classMil.OddDisplayRule, m_classMil.OddImageRule, m_CtrlDisp2.GetSafeHwnd());
	MdispSelectWindow(m_classMil.EvenDisplayRule, m_classMil.EvenImageRule, m_CtrlDisp3.GetSafeHwnd());
	MdispSelectWindow(m_classMil.EvenDisplayAI, m_classMil.EvenImageAI, m_CtrlDisp5.GetSafeHwnd());
	str2log(&m_ctrl_log, string("[성공] 카메라 초기화가 완료되었습니다."));
	m_ctrl_log.SetTopIndex(m_ctrl_log.GetCount() - 1);
	AfxMessageBox(_T("프로그램 초기화가 완료되었습니다."));
	m_ButtonInit.EnableWindow(FALSE);
	m_ButtonSave.EnableWindow(TRUE);
}


void CKWBaseFormDlg::OnBnClickedBtnInit()
{
	m_classMil.Allocation(0);
	m_classMil.Alloc_MIL_ImageBuffer();

	//MdispSelectWindow(m_classMil.OddImageDisplay, m_classMil.OddImage, m_CtrlDisp0.GetSafeHwnd());
	//MdispSelectWindow(m_classMil.EvenImageDisplay, m_classMil.EvenImage, m_CtrlDisp1.GetSafeHwnd());

	MdispSelectWindow(m_classMil.OddDisplayRule, m_classMil.OddImageRule, m_CtrlDisp2.GetSafeHwnd());
	MdispSelectWindow(m_classMil.EvenDisplayRule, m_classMil.EvenImageRule, m_CtrlDisp3.GetSafeHwnd());
	MdispSelectWindow(m_classMil.EvenDisplayAI, m_classMil.EvenImageAI, m_CtrlDisp5.GetSafeHwnd());

	//MdispControl(m_classMil.OddImageDisplay, M_UPDATE, M_DISABLE);
	//MdispControl(m_classMil.EvenImageDisplay, M_UPDATE, M_DISABLE);
	//MdispControl(m_classMil.OddDisplayRule, M_UPDATE, M_DISABLE);
	//MdispControl(m_classMil.EvenDisplayRule, M_UPDATE, M_DISABLE);
	//MdispControl(m_classMil.EvenDisplayAI, M_UPDATE, M_DISABLE);

	//str2log(&m_ctrl_log, string("[MESSAGE] MIL & Model Init OK!"));

	AfxMessageBox(_T("프로그램 초기화 셋팅이 완료되었습니다."));
	m_ButtonInit.EnableWindow(FALSE);
	m_ButtonSave.EnableWindow(TRUE);
}
// 이미지 분할 알고리즘 코드
void CKWBaseFormDlg::ImageSplit() 
{
	//cout << "imgSaved = true // start Detection" << endl;
	m_classMil.CAM1.imgSaved = false;
	str2log(&m_ctrl_log, string("[성공] 이미지 캡쳐가 완료되었습니다."));
	m_ctrl_log.SetTopIndex(m_ctrl_log.GetCount() - 1);
	//str2log(&m_ctrl_log, string("[MESSAGE] Resolution is ### 51um ### !"));

	Mat image = m_classMil.CAM1.GrabImage;

	if (image.empty()) {
		cout << "이미지를 불러올 수 없습니다." << endl;
	}
	// Split start //////////////////////////////////////////////////////////

	// 이미지의 높이와 너비 가져오기
	height = image.rows; // 7000
	width = image.cols; // 4096

	cout << "W : " << width << " / H : " << height << endl;

	Size newSize(width, height / 2); // 4096 , 3500

	// 홀수 픽셀과 짝수 픽셀을 저장할 빈 캔버스 생성
	odd_pixel_canvas = Mat::zeros(newSize, image.type());
	even_pixel_canvas = Mat::zeros(newSize, image.type());

	int even_y = 0, odd_y = 0;

	// 이미지의 모든 픽셀에 대해 반복
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			// 홀수 픽셀과 짝수 픽셀로 나누기
			if (y % 2 == 0) {
				even_pixel_canvas.at<Vec3b>(even_y, x) = image.at<Vec3b>(y, x);
				//cout << "even = " << y << " " << x << endl;
			}
			else {
				odd_pixel_canvas.at<Vec3b>(odd_y, x) = image.at<Vec3b>(y, x);
				//cout << "odd = " << y << " " << x << endl;
			}
		}
		if (y % 2 == 0) {
			even_y++;
		}
		else {
			odd_y++;
		}
	}

	// 결과 이미지 저장(odd, even 구분 로직)
	float even_result = 0;
	float odd_result = 0;
	OverLapDetection::detect(even_pixel_canvas, 0, 1, &even_result);
	OverLapDetection::detect(odd_pixel_canvas, 0, 1, &odd_result);
	if (even_result > odd_result) {
		Mat temp;
		temp = odd_pixel_canvas;
		odd_pixel_canvas = even_pixel_canvas;
		even_pixel_canvas = temp;
	}
	imwrite(save_image_path_odd, odd_pixel_canvas);
	imwrite(save_image_path_even, even_pixel_canvas);
}
// 구멍 개수 및 겹침 검사 ( 하부 조명 )
void CKWBaseFormDlg::DetectionHoleRule()
{
	str2log(&m_ctrl_log, string("[진행] 하부 조명 검사를 시작합니다."));
	m_ctrl_log.SetTopIndex(m_ctrl_log.GetCount() - 1);
	auto start = std::chrono::system_clock::now();
	High_Frame = odd_pixel_canvas.clone();
	Mat High_Convert;
	vector<cv::Mat> channels;
	start = std::chrono::system_clock::now();
	// OverLapDetection
	DetectionHoleRule_overlap_result = OverLapDetection::detect(odd_pixel_canvas, 32, 9);

	// High_Frame Processing
	cvtColor(High_Frame, High_Convert, COLOR_BGR2HLS);
	split(High_Convert, channels);
	for (int i = 0; i < channels.size(); ++i) {
		cv::normalize(channels[i], channels[i], 0, 255, NORM_MINMAX);
	}

	merge(channels, High_Convert);
	Mat High_Gray;
	cvtColor(High_Convert, High_Gray, cv::COLOR_BGR2GRAY);
	// 이진화
	Mat High_Binary;
	threshold(High_Gray, High_Binary, 130, 255, THRESH_BINARY);
	// GaussianBlur(High_Binary, High_Binary, cv::Size(5, 5), 0);

	DetectionHoleRule_HoleCount = 0;
	vector<double> vHoleSize;
	//DetectionHoleRule_fHoleMinSize;

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(High_Binary, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	// 각 컨투어의 면적 계산 및 출력
	for (size_t i = 0; i < contours.size(); ++i) {

		double area = cv::contourArea(contours[i]);

		if (area > 400)
		{
			// 블롭을 원본 이미지에 그리기
			//std::cout << "Contour " << i << " has an area of: " << area << endl;
			vHoleSize.push_back(area);
			DetectionHoleRule_HoleCount++;
			drawContours(High_Frame, contours, i, cv::Scalar(0, 0, 255), 5);
		}
	}
	auto end = std::chrono::system_clock::now();
	DetectionHoleRuleTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	if (!vHoleSize.empty()) {
		auto min_it = min_element(vHoleSize.begin(), vHoleSize.end());
		cout << "Min Size : " << *min_it << endl;
		DetectionHoleRule_fHoleMinSize = *min_it;
	}
	
	bDetectionHoleRuleFinish = true;
	str2log(&m_ctrl_log, string("[성공] 구멍 개수 및 겹침 검사가 완료되었습니다."));
	m_ctrl_log.SetTopIndex(m_ctrl_log.GetCount() - 1);
}
// 규칙기반으로 이물질 검사하는 코드 ( 상부 조명 )
void CKWBaseFormDlg::DetectionNumRule()
{
	str2log(&m_ctrl_log, string("[시작] 이물 검출(규칙 기반) 검사를 시작합니다."));
	m_ctrl_log.SetTopIndex(m_ctrl_log.GetCount() - 1);
	auto start = std::chrono::system_clock::now();
	Low_Frame = even_pixel_canvas;
	Mat Low_Convert;
	DetectionNumRule_Low_Def_Count = 0;
	cvtColor(Low_Frame, Low_Convert, COLOR_BGR2HSV);

	vector<cv::Mat> channels;
	split(Low_Convert, channels);

	for (int i = 0; i < channels.size(); ++i) {
		cv::normalize(channels[i], channels[i], 0, 255, NORM_MINMAX);
	}
	merge(channels, Low_Convert);

	Mat Low_Gray;
	cvtColor(Low_Convert, Low_Gray, COLOR_BGR2GRAY);

	float average_brightness = mean(Low_Gray)[0];

	// cout << "평균 밝기 : " << average_brightness << endl;
	// 이진화
	Mat Low_Binary;
	threshold(Low_Gray, Low_Binary, 130, 255, THRESH_BINARY);
	

	//블러
	GaussianBlur(Low_Binary, Low_Binary, cv::Size(5, 5), 0);
	//medianBlur(Low_Binary, Low_Binary, 7);
	// 
	//Mat Low_Bilateral;
	//bilateralFilter(Low_Binary, Low_Bilateral, 11, 75, 75);

	// 컨투어
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(Low_Binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	// 각 컨투어의 면적 계산 및 출력
	for (size_t i = 0; i < contours.size(); ++i) {
		double area = contourArea(contours[i]);
		if (area >= 550)
		{
			// 블롭을 원본 이미지에 그리기
			//cout << "Contour " << i << " / area : " << area << endl;
			DetectionNumRule_Low_Def_Count++;
			drawContours(Low_Frame, contours, i, cv::Scalar(0, 255, 0), 3);
			putText(Low_Frame, std::to_string(i), contours[i][0], FONT_HERSHEY_SIMPLEX, 2, Scalar(255, 255, 255), 3);
		}
	}
	//imwrite("./image/rule.png", Low_Frame);

	auto end = std::chrono::system_clock::now();
	DetectionNumRuleTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	bDetectionNumRuleFinish = true;
	str2log(&m_ctrl_log, string("[성공] 이물 검출 (규칙 완료되었습니다."));
	m_ctrl_log.SetTopIndex(m_ctrl_log.GetCount() - 1);
}
// run_detection을 호출해서 딥러닝 Frame 이미지를 얻어옴
void CKWBaseFormDlg::DetectionNumDeepLearn()
{
	//아래 코드에서 걸림
	//str2log(&m_ctrl_log, string("[MESSAGE] DL Inspection Start!"));
	//ProcessWindowMessage();
	//str2log(&m_ctrl_log, string("[MESSAGE] DL Inspection End!"));
	//ProcessWindowMessage();

	DL_Frame = even_detection.run_detection(save_image_path_even);
	bDetectionNumDeepLearnFinish = true;
}
// 하부조명 호출 스레드
UINT DetectionHoleRuleThread(LPVOID pParam) {
	CKWBaseFormDlg* pDlg = (CKWBaseFormDlg*)pParam;
	if (pDlg != nullptr) {
		cout << " DetectionHoleRule Start   " << endl;
		pDlg->DetectionHoleRule();
	}
	return 0;
}
// 이물 개수(규칙기반) 호출 스레드
UINT DetectionNumRuleThread(LPVOID pParam) {
	CKWBaseFormDlg* pDlg = (CKWBaseFormDlg*)pParam;
	if (pDlg != nullptr) {
		cout << " DetectionNumRule  Start   " << endl;
		pDlg->DetectionNumRule();
	}
	return 0;
}
// 이물 개수(딥러닝) 호출 스레드
UINT DetectionNumDeepLearnThread(LPVOID pParam) {
	CKWBaseFormDlg* pDlg = (CKWBaseFormDlg*)pParam;
	if (pDlg != nullptr) {
		cout << " DetectionNumDeepLearn Start   " << endl;
		pDlg->DetectionNumDeepLearn();
	}
	return 0;
}

void CKWBaseFormDlg::OnBnClickedBtnSave()
{
	m_ButtonSave.EnableWindow(FALSE);
	m_ctrl_log.ResetContent();
	
	//CFont logFont;
	//logFont.CreatePointFont(200, _T("굴림"));
	//m_ctrl_log.SetFont(&logFont);

	str2log(&m_ctrl_log, string("[시작] 김 검사를 시작합니다."));
	m_ctrl_log.SetTopIndex(m_ctrl_log.GetCount() - 1);
	str2log(&m_ctrl_log, string("[진행] 이미지 획득을 시작합니다."));
	m_ctrl_log.SetTopIndex(m_ctrl_log.GetCount() - 1);
	motor.move_once(87, 350, 208, 900);

	m_classMil.CAM1.imgSaved = false;
	m_classMil.GrabProcess_Line2();
	cout << " out GrabProcess_Line2   " << endl;
	ProcessWindowMessage();
	bDetectionHoleRuleFinish = false;
	bDetectionNumRuleFinish = false;
	bDetectionNumDeepLearnFinish = false;
	while (true) {
		std::this_thread::sleep_for(std::chrono::nanoseconds(1));
		//cout << m_classMil.CAM1.imgSaved << endl;
		if (m_classMil.CAM1.imgSaved == true) {

			ImageSplit();
			ProcessWindowMessage();
			str2log(&m_ctrl_log, string("[성공] 이미지 분할이 완료되었습니다."));
			ProcessWindowMessage();

			//png 저장(학습 데이터)
			std::stringstream ss1;
			std::stringstream ss2;
			//ss1 << ".\\odd_image\\" << "odd_image_" << count << ".png";
			//ss2 << ".\\even_image\\" << "even_image_" << count << ".png";
			ss1 << ".\\image\\" << "odd_png_image_" << ".png";
			ss2 << ".\\image\\" << "even_png_image" << ".png";
			imwrite(ss1.str(), odd_pixel_canvas);
			imwrite(ss2.str(), even_pixel_canvas);
			count++;

			CWinThread* pThread = AfxBeginThread(::DetectionHoleRuleThread, this); // THread 1
			CWinThread* pThread2 = AfxBeginThread(::DetectionNumRuleThread, this); // THread 1
			CWinThread* pThread3 = AfxBeginThread(::DetectionNumDeepLearnThread, this); // THread 1

			auto tstart = std::chrono::system_clock::now();
			while (true)
			{
				std::this_thread::sleep_for(std::chrono::nanoseconds(1));
				//std::cout << bDetectionHoleRuleFinish << bDetectionNumDeepLearnFinish << bDetectionNumRuleFinish << std::endl;
				if (bDetectionHoleRuleFinish && bDetectionNumRuleFinish && bDetectionNumDeepLearnFinish)
				{
					break;
				}
			}
			chrono::duration<double>sec = std::chrono::system_clock::now() - tstart;
			cout << "total Processing Time : \n" << sec.count() * 1000 << "miliseconds" << endl;


			//하부조명 결과값 출력 처리
			PrintHoleRule();
			//이물개수(규칙기반) 결과값 출력 처리
			PrintNumRule();
			//이물개수(딥러닝) 결과값 출력 처리
			PrintNumDeepLearn();


			
			
			
			// DL Inspection
			




			//WaitForSingleObject(pThread->m_hThread, INFINITE);
			//CloseHandle(pThread->m_hThread);
			//delete pThread;
			//DetectionNumDeepLearn();
			str2log(&m_ctrl_log, string("[성공] 모든 검사가 완료되었습니다!"));
			m_ctrl_log.SetTopIndex(m_ctrl_log.GetCount() - 1);
			
			//AfxMessageBox(_T("Inspection OK!"));
			m_ButtonSave.EnableWindow(TRUE);
			break;
		}
		
	}
	
}

void CKWBaseFormDlg::PrintHoleRule()
{
	MbufPutColor2d(m_classMil.OddImageRule, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, width, height / 2, High_Frame.data);
	CString cstr_Hole_Count;
	cstr_Hole_Count.Format(_T(" %d"), DetectionHoleRule_HoleCount);
	Hole_Count.SetWindowTextW(cstr_Hole_Count);
	CString cstr_Hole_Double;
	cstr_Hole_Double = DetectionHoleRule_overlap_result ? _T(" 겹침(2장 이상)") : _T(" 겹치지 않음");
	Hole_Double.SetWindowTextW(cstr_Hole_Double);
	CString cstr_Hole_MinSize;
	cstr_Hole_MinSize.Format(_T(" %.2f"), DetectionHoleRule_fHoleMinSize * 0.0025); // 50um 기준
	Hole_MinSize.SetWindowTextW(cstr_Hole_MinSize);

	string str_Time2 = to_string(DetectionHoleRuleTime.count());

	CString cstr_Time2;
	cstr_Time2 = str_Time2.c_str();
	Hole_Time.SetWindowTextW(cstr_Time2);

}
void CKWBaseFormDlg::PrintNumRule()
{
	MbufPutColor2d(m_classMil.EvenImageRule, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, width, height / 2, Low_Frame.data);
	string str_Time1 = to_string(DetectionNumRuleTime.count());
	CString cstr_Time1;
	cstr_Time1 = str_Time1.c_str();
	EvenRuleInspecTime.SetWindowTextW(cstr_Time1);

	// 카운트 출력
	CString cstr_EvenRuleDefactCount;
	cstr_EvenRuleDefactCount.Format(_T(" %d"), DetectionNumRule_Low_Def_Count);
	EvenRuleDefactCount.SetWindowTextW(cstr_EvenRuleDefactCount);
}
void CKWBaseFormDlg::PrintNumDeepLearn()
{
	MbufPutColor2d(m_classMil.EvenImageAI, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, width, height / 2, DL_Frame.image.data); 

	imwrite(".\\Image\\AI_EVEN_Y.bmp", DL_Frame.image);

	CString cstr_Time3;
	cstr_Time3.Format(_T(" %d"), DL_Frame.total_inference_time);
	EvenDL_Time.SetWindowTextW(cstr_Time3);

	CString cstr_Defect_Count;
	cstr_Defect_Count.Format(_T(" %d"), DL_Frame.object_count);
	EvenDL_Count.SetWindowTextW(cstr_Defect_Count);

	CString cstr_Defect_Score;
	cstr_Defect_Score.Format(_T(" %d"), DL_Frame.objectScoreThreshold);
	EvenDL_Score.SetWindowTextW(cstr_Defect_Score);
}


void CKWBaseFormDlg::OnBnClickedBtnZoom()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_classMil.ZoomImage != NULL)
	{
		MbufCopy(m_classMil.EvenImageAI, m_classMil.ZoomImage);
		MdispSelect(m_classMil.MilZoomDisp, m_classMil.ZoomImage);
	}
	else cout << " No Data in Buffer" << endl;
}

void CKWBaseFormDlg::OnBnClickedBtnZoomRule()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_classMil.ZoomImage != NULL)
	{
		MbufCopy(m_classMil.EvenImageRule, m_classMil.ZoomImage);
		MdispSelect(m_classMil.MilZoomDisp, m_classMil.ZoomImage);
	}
	else cout << " No Data in Buffer" << endl;
}

void CKWBaseFormDlg::OnBnClickedBtnZoomHole()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_classMil.ZoomImage != NULL)
	{
		MbufCopy(m_classMil.OddImageRule, m_classMil.ZoomImage);
		MdispSelect(m_classMil.MilZoomDisp, m_classMil.ZoomImage);
	}
	else cout << " No Data in Buffer" << endl;
}

void CKWBaseFormDlg::str2log(CListBox* logbox, string content)
{
	CString cstr;
	cstr = content.c_str();
	logbox->AddString(cstr);
}

void CKWBaseFormDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1)
	{
		m_ctrl_log.RedrawWindow(); 
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CKWBaseFormDlg::ProcessWindowMessage()
{
	MSG msg;

	while (::PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
	{
		::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
	}
}

void CKWBaseFormDlg::OnBnClickedBtnInspec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// RuleBase Inspection
	//str2log(&m_ctrl_log, string("[진행] 규칙기반 검사를 시작합니다."));

	auto start = std::chrono::system_clock::now();

	Mat Low_Frame = even_pixel_canvas;
	Mat Low_Convert;

	int Low_Def_Count = 0;

	cvtColor(Low_Frame, Low_Convert, COLOR_BGR2HSV);

	vector<cv::Mat> channels;
	split(Low_Convert, channels);

	for (int i = 0; i < channels.size(); ++i) {
		cv::normalize(channels[i], channels[i], 0, 255, NORM_MINMAX);
	}

	merge(channels, Low_Convert);

	Mat Low_Gray;
	cvtColor(Low_Convert, Low_Gray, COLOR_BGR2GRAY);

	// 이진화
	Mat Low_Binary;
	threshold(Low_Gray, Low_Binary, 150, 255, THRESH_BINARY);
	// GaussianBlur(Low_Binary, Low_Binary, cv::Size(5, 5), 0);

	// 컨투어
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(Low_Binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	// 각 컨투어의 면적 계산 및 출력
	for (size_t i = 0; i < contours.size(); ++i) {

		double area = contourArea(contours[i]);

		if (area >= 700)
		{
			// 블롭을 원본 이미지에 그리기
			cout << "Contour " << i << " / area : " << area << endl;
			Low_Def_Count++;
			drawContours(Low_Frame, contours, i, cv::Scalar(0, 255, 0), 3);
		}
	}

	auto end = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	// Time 출력
	string str_Time1 = to_string(duration.count());
	CString cstr_Time1;
	cstr_Time1 = str_Time1.c_str();
	EvenRuleInspecTime.SetWindowTextW(cstr_Time1);

	// 카운트 출력
	CString cstr_EvenRuleDefactCount;
	cstr_EvenRuleDefactCount.Format(_T(" %d"), Low_Def_Count);
	EvenRuleDefactCount.SetWindowTextW(cstr_EvenRuleDefactCount);

	Mat Temp = Low_Frame;

	MbufPutColor2d(m_classMil.EvenImageRule, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, width, height / 2, (void*)Temp.data); // Low RuleBase

	//// Hole Inspection ########################################################################
	//Mat High_Frame = odd_pixel_canvas.clone();
	//Mat High_Convert;

	//start = std::chrono::system_clock::now();

	//// High_Frame Processing
	//cvtColor(High_Frame, High_Convert, COLOR_BGR2HLS);
	//split(High_Convert, channels);

	//for (int i = 0; i < channels.size(); ++i) {
	//	cv::normalize(channels[i], channels[i], 0, 255, NORM_MINMAX);
	//}

	//merge(channels, High_Convert);
	//Mat High_Gray;
	//cvtColor(High_Convert, High_Gray, cv::COLOR_BGR2GRAY);

	//// 이진화
	//Mat High_Binary;
	//threshold(High_Gray, High_Binary, 200, 255, THRESH_BINARY);
	//// GaussianBlur(High_Binary, High_Binary, cv::Size(5, 5), 0);

	//int nHoleCount = 0;
	//vector<double> vHoleSize;
	//float fHoleMinSize;

	//findContours(High_Binary, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	//// 각 컨투어의 면적 계산 및 출력
	//for (size_t i = 0; i < contours.size(); ++i) {

	//	double area = cv::contourArea(contours[i]);

	//	if (area > 400)
	//	{
	//		// 블롭을 원본 이미지에 그리기
	//		std::cout << "Contour " << i << " has an area of: " << area << endl;
	//		vHoleSize.push_back(area);
	//		nHoleCount++;
	//		drawContours(High_Frame, contours, i, cv::Scalar(0, 0, 255), -1);
	//	}
	//}

	//end = std::chrono::system_clock::now();
	//duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	//if (!vHoleSize.empty()) {
	//	auto min_it = min_element(vHoleSize.begin(), vHoleSize.end());
	//	cout << "Min Size : " << *min_it << endl;
	//	fHoleMinSize = *min_it;
	//}

	//CString cstr_Hole_Count;
	//cstr_Hole_Count.Format(_T(" %d"), nHoleCount);
	//Hole_Count.SetWindowTextW(cstr_Hole_Count);

	//CString cstr_Hole_MinSize;
	//cstr_Hole_MinSize.Format(_T(" %.2f"), fHoleMinSize * 0.0025); // 50um 기준
	//Hole_MinSize.SetWindowTextW(cstr_Hole_MinSize);

	//string str_Time2 = to_string(duration.count());
	//CString cstr_Time2;
	//cstr_Time2 = str_Time2.c_str();
	//Hole_Time.SetWindowTextW(cstr_Time2);

	//MbufPutColor2d(m_classMil.OddImageRule, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, width, height / 2, High_Frame.data); // High RuleBase

	ProcessWindowMessage();
	//str2log(&m_ctrl_log, string("[성공] 이물검사(규칙기반)이 완료되었습니다."));
}


void CKWBaseFormDlg::OnBnClickedBtnTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
