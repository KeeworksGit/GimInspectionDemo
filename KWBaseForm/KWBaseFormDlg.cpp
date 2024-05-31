
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
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
	m_ButtonSave.LoadBitmaps(IDB_StartBtn);
	m_ButtonInit.LoadBitmaps(IDB_InitBtn);
	m_btn_zoom.LoadBitmaps(IDB_BITMAP2);
	m_btn_zoomrule .LoadBitmaps(IDB_BITMAP2);
	m_btn_zoomhole.LoadBitmaps(IDB_BITMAP2);

	CRect buttonRect;
	CRect rect;
	GetWindowRect(&rect);
	int width = 1920;  // 새로운 너비
	int height = 1080; // 새로운 높이
	SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);

	SetWindowText(_T("Keeworks_Inspection_Module_V1.0"));

	m_CtrlDisp0.SetWindowPos(NULL, 43, 159, 458, 391, SWP_NOSENDCHANGING); //odd
	m_CtrlDisp1.SetWindowPos(NULL, 43, 600, 458, 391, SWP_NOSENDCHANGING); //even
	m_CtrlDisp2.SetWindowPos(NULL, 542, 159, 458, 391, SWP_NOSENDCHANGING); //
	m_CtrlDisp3.SetWindowPos(NULL, 542, 600, 458, 391, SWP_NOSENDCHANGING); //
	m_CtrlDisp5.SetWindowPos(NULL, 1225, 600, 458, 391, SWP_NOSENDCHANGING);

	m_ButtonInit.SetWindowPos(NULL, 1306, 180, 238, 54, SWP_NOSENDCHANGING); // INIT 버튼
	m_ButtonSave.SetWindowPos(NULL, 1578, 180, 238, 54, SWP_NOSENDCHANGING); // 결과 저장 버튼
	m_btn_zoom.SetWindowPos(NULL, 1659, 567, 24, 24, SWP_NOSENDCHANGING);
	m_btn_zoomrule.SetWindowPos(NULL, 976, 567, 24, 24, SWP_NOSENDCHANGING);
	m_btn_zoomhole.SetWindowPos(NULL, 976, 126, 24, 24, SWP_NOSENDCHANGING);

	EvenRuleDefactCount.SetWindowPos(NULL, 1021, 631, 183, 33, SWP_NOSENDCHANGING);
	EvenRuleInspecTime.SetWindowPos(NULL, 1021, 718, 183, 33, SWP_NOSENDCHANGING);
	EvenDL_Count.SetWindowPos(NULL, 1704, 631, 183, 33, SWP_NOSENDCHANGING);
	EvenDL_Time.SetWindowPos(NULL, 1704, 718, 183, 33, SWP_NOSENDCHANGING);
	EvenDL_Score.SetWindowPos(NULL, 1704, 805, 183, 33, SWP_NOSENDCHANGING);

	Hole_Count.SetWindowPos(NULL, 1021, 190, 183, 33, SWP_NOSENDCHANGING);
	Hole_Double.SetWindowPos(NULL, 1021, 277, 183, 33, SWP_NOSENDCHANGING);
	Hole_MinSize.SetWindowPos(NULL, 1021, 364, 183, 33, SWP_NOSENDCHANGING);
	Hole_Time.SetWindowPos(NULL, 1021, 454, 183, 33, SWP_NOSENDCHANGING);

	m_ctrl_log.SetWindowPos(NULL, 1226, 288, 661, 222, SWP_NOSENDCHANGING);

	// MIL 관련 초기화 
	// MIL로 띄울 이미지 odd, even buf할당
	
	// 최종 결과물을 가질 MIL_ID Rule 2개 AI 2개
	// 토탈 MIL_ID 이미지 버퍼 6개 할당

	//motor init
	motor.init();

	string result_message = "[MESSAGE] Motor Init OK!";
	cout << result_message << endl;
	str2log(&m_ctrl_log, result_message);

	AfxMessageBox(_T("Motor Init OK!"));

	m_ButtonInit.EnableWindow(TRUE);
	m_ButtonSave.EnableWindow(FALSE);

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
		bmp.LoadBitmap(IDB_BITMAP1);
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

void CKWBaseFormDlg::OnBnClickedBtnInit()
{
	//model load init
	even_detection.model_init("./0531_1403_best.saigedet", 90);

	m_classMil.Allocation(0);
	m_classMil.Alloc_MIL_ImageBuffer();

	MdispSelectWindow(m_classMil.OddImageDisplay, m_classMil.OddImage, m_CtrlDisp0.GetSafeHwnd());
	MdispSelectWindow(m_classMil.EvenImageDisplay, m_classMil.EvenImage, m_CtrlDisp1.GetSafeHwnd());
	MdispSelectWindow(m_classMil.OddDisplayRule, m_classMil.OddImageRule, m_CtrlDisp2.GetSafeHwnd());
	MdispSelectWindow(m_classMil.EvenDisplayRule, m_classMil.EvenImageRule, m_CtrlDisp3.GetSafeHwnd());
	MdispSelectWindow(m_classMil.EvenDisplayAI, m_classMil.EvenImageAI, m_CtrlDisp5.GetSafeHwnd());

	//MdispControl(m_classMil.OddImageDisplay, M_UPDATE, M_DISABLE);
	//MdispControl(m_classMil.EvenImageDisplay, M_UPDATE, M_DISABLE);
	//MdispControl(m_classMil.OddDisplayRule, M_UPDATE, M_DISABLE);
	//MdispControl(m_classMil.EvenDisplayRule, M_UPDATE, M_DISABLE);
	//MdispControl(m_classMil.EvenDisplayAI, M_UPDATE, M_DISABLE);

	str2log(&m_ctrl_log, string("[MESSAGE] MIL & Model Init OK!"));

	AfxMessageBox(_T("MIL & Model Init OK!"));
	m_ButtonInit.EnableWindow(FALSE);
	m_ButtonSave.EnableWindow(TRUE);
}

void CKWBaseFormDlg::OnBnClickedBtnSave()
{
	m_ButtonSave.EnableWindow(FALSE);

	str2log(&m_ctrl_log, string("[MESSAGE] Inspection Start!"));
	str2log(&m_ctrl_log, string("[MESSAGE] Camera Grab Start!"));
	motor.move_once(90, 350, 208, 900);

	m_classMil.CAM1.imgSaved = false;
	m_classMil.GrabProcess_Line2();
	cout << " out GrabProcess_Line2   " << endl;
	ProcessWindowMessage();
	while (true) {
		cout << m_classMil.CAM1.imgSaved << endl;
		if (m_classMil.CAM1.imgSaved == true) {
			cout << "imgSaved = true // start Detection" << endl;
			m_classMil.CAM1.imgSaved = false;
			str2log(&m_ctrl_log, string("[MESSAGE] Camera Grab End!"));
			str2log(&m_ctrl_log, string("[MESSAGE] Resolution is ### 50um ### !"));

			Mat image = m_classMil.CAM1.GrabImage;

			if (image.empty()) {
				cout << "이미지를 불러올 수 없습니다." << endl;
			}

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
			// 결과 이미지 저장  //////////////////////

			/*Scalar s1 = mean(odd_pixel_canvas);
			Scalar s2 = mean(even_pixel_canvas);

			if (s1[0] < s2[0])
			{
				지금 안됨, 중간을 따던가 해야함
				Mat temp;
				temp = odd_pixel_canvas;

				odd_pixel_canvas = even_pixel_canvas;

				even_pixel_canvas = temp;
			}*/
			
			imwrite(save_image_path_odd, odd_pixel_canvas);
			imwrite(save_image_path_even, even_pixel_canvas);

			//학습data 저장
			//std::stringstream ss1;
			//std::stringstream ss2;
			//ss1 << ".\\odd_image\\" << "odd_image_" << count << ".png";
			//ss2 << ".\\even_image\\" << "even_image_" << count << ".png";
			//imwrite(ss1.str(), odd_pixel_canvas);
			//imwrite(ss2.str(), even_pixel_canvas);
			//count++;=

			Mat temp1 = odd_pixel_canvas;
			Mat temp2 = even_pixel_canvas;

			MbufPutColor2d(m_classMil.OddImage, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, width, height / 2, (void*)temp1.data);
			MbufPutColor2d(m_classMil.EvenImage, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, width, height / 2, (void*)temp2.data);

			ProcessWindowMessage();
			str2log(&m_ctrl_log, string("[MESSAGE] Grab Image Split OK!"));
			ProcessWindowMessage();
			



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

			MbufPutColor2d(m_classMil.EvenImageRule, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, width, height / 2, (void*)Temp.data);

			////////////////////////////////////////////////   low end
			Mat High_Frame = odd_pixel_canvas.clone();
			Mat High_Convert;

			start = std::chrono::system_clock::now();

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
			threshold(High_Gray, High_Binary, 200, 255, THRESH_BINARY);
			// GaussianBlur(High_Binary, High_Binary, cv::Size(5, 5), 0);

			int nHoleCount = 0;
			vector<double> vHoleSize;
			float fHoleMinSize;

			findContours(High_Binary, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

			// 각 컨투어의 면적 계산 및 출력
			for (size_t i = 0; i < contours.size(); ++i) {

				double area = cv::contourArea(contours[i]);

				if (area > 400)
				{
					// 블롭을 원본 이미지에 그리기
					std::cout << "Contour " << i << " has an area of: " << area << endl;
					vHoleSize.push_back(area);
					nHoleCount++;
					drawContours(High_Frame, contours, i, cv::Scalar(0, 0, 255), -1);
				}
			}

			end = std::chrono::system_clock::now();
			duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

			if (!vHoleSize.empty()) {
				auto min_it = min_element(vHoleSize.begin(), vHoleSize.end());
				cout << "Min Size : " << *min_it << endl;
				fHoleMinSize = *min_it;
			}

			CString cstr_Hole_Count;
			cstr_Hole_Count.Format(_T(" %d"), nHoleCount);
			Hole_Count.SetWindowTextW(cstr_Hole_Count);

			CString cstr_Hole_MinSize;
			cstr_Hole_MinSize.Format(_T(" %.2f"), fHoleMinSize * 0.0025); // 50um 기준
			Hole_MinSize.SetWindowTextW(cstr_Hole_MinSize);

			string str_Time2 = to_string(duration.count());
			CString cstr_Time2;
			cstr_Time2 = str_Time2.c_str();
			Hole_Time.SetWindowTextW(cstr_Time2);

			MbufPutColor2d(m_classMil.OddImageRule, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, width, height / 2, High_Frame.data);

			//// DL Inspection
			str2log(&m_ctrl_log, string("[MESSAGE] DL Inspection Start!"));
			ProcessWindowMessage();
			DetectionResult result = even_detection.run_detection(save_image_path_even);
			ProcessWindowMessage();
			MbufPutColor2d(m_classMil.EvenImageAI, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, width, height / 2, result.image.data); // Low AI
			imwrite(".\\Image\\AI_EVEN_Y.bmp", result.image);
			ProcessWindowMessage();
			str2log(&m_ctrl_log, string("[MESSAGE] DL Inspection End!"));

			str2log(&m_ctrl_log, string("[MESSAGE] All Inspection Complete!"));

			AfxMessageBox(_T("Inspection OK!"));
			m_ButtonSave.EnableWindow(TRUE);

			break;
		}
		
	}
	
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
	str2log(&m_ctrl_log, string("[MESSAGE] RuleBase Defact Inspection Start!"));

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
	str2log(&m_ctrl_log, string("[MESSAGE] RuleBase Defact Inspection End!"));
}
