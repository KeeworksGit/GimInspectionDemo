
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
	DDX_Control(pDX, IDC_DISP_4, m_CtrlDisp4);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ButtonSave);
	DDX_Control(pDX, IDC_BTN_INIT, m_ButtonInit);

	DDX_Control(pDX, IDC_DISP_5, m_CtrlDisp5);
	DDX_Control(pDX, IDC_EDIT1, OddRuleDefactCount);
	DDX_Control(pDX, IDC_EDIT2, OddRuleInspecTime);
	DDX_Control(pDX, IDC_EDIT3, EvenRuleDefactCount);
	DDX_Control(pDX, IDC_EDIT4, EvenRuleInspecTime);
	DDX_Control(pDX, IDC_EDIT5, OddDL_Count);
	DDX_Control(pDX, IDC_EDIT6, OddDL_Time);
	DDX_Control(pDX, IDC_EDIT7, EvenDL_Count);
	DDX_Control(pDX, IDC_EDIT8, EvenDL_Time);
}

BEGIN_MESSAGE_MAP(CKWBaseFormDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_INIT, &CKWBaseFormDlg::OnBnClickedBtnInit)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CKWBaseFormDlg::OnBnClickedBtnSave)	
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
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_ButtonSave.LoadBitmaps(IDB_StartBtn);
	m_ButtonInit.LoadBitmaps(IDB_InitBtn);
	m_Bitmap.LoadBitmap(IDB_BG);

	HRESULT hr = BG_Image.Load(_T(".\\Resource\\BackGroundImage.bmp"));

	StartButtonImg.Load(_T(".\\Resource\\StartButtonImage.bmp"));
	InitButtonImg.Load(_T(".\\Resource\\InitButtonImage.bmp"));

	CRect buttonRect;
	CRect rect;
	
	GetWindowRect(&rect);

	int width = 1920;  // 새로운 너비
	int height = 1080; // 새로운 높이
	SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);

	m_CtrlDisp0.SetWindowPos(NULL, 43, 176, 458, 391, SWP_NOSENDCHANGING); //odd
	m_CtrlDisp1.SetWindowPos(NULL, 43, 617, 458, 391, SWP_NOSENDCHANGING); //even
	m_CtrlDisp2.SetWindowPos(NULL, 542, 176, 458, 391, SWP_NOSENDCHANGING); //
	m_CtrlDisp3.SetWindowPos(NULL, 542, 617, 458, 391, SWP_NOSENDCHANGING); //
	m_CtrlDisp4.SetWindowPos(NULL, 1225, 176, 458, 391, SWP_NOSENDCHANGING); //
	m_CtrlDisp5.SetWindowPos(NULL, 1225, 617, 458, 391, SWP_NOSENDCHANGING);

	m_ButtonInit.SetWindowPos(NULL, 1383, 30, 238, 54, SWP_NOSENDCHANGING); // INIT 버튼
	m_ButtonSave.SetWindowPos(NULL, 1649, 30, 238, 54, SWP_NOSENDCHANGING); // 결과 저장 버튼


	OddRuleDefactCount.SetWindowPos(NULL, 1021, 215, 183, 43, SWP_NOSENDCHANGING);;
	OddRuleInspecTime.SetWindowPos(NULL, 1021, 300, 183, 43, SWP_NOSENDCHANGING);;
	EvenRuleDefactCount.SetWindowPos(NULL, 1021, 650, 183, 43, SWP_NOSENDCHANGING);;
	EvenRuleInspecTime.SetWindowPos(NULL, 1021, 735, 183, 43, SWP_NOSENDCHANGING);;
	OddDL_Count.SetWindowPos(NULL, 1704, 215, 183, 43, SWP_NOSENDCHANGING);;
	OddDL_Time.SetWindowPos(NULL, 1704, 300, 183, 43, SWP_NOSENDCHANGING);;
	EvenDL_Count.SetWindowPos(NULL, 1704, 650, 183, 43, SWP_NOSENDCHANGING);;
	EvenDL_Time.SetWindowPos(NULL, 1704, 735, 183, 43, SWP_NOSENDCHANGING);;

	//MIL 관련 초기화 
	//MIL로 띄울 이미지 odd, even buf할당
	// 최종 결과물을 가질 MIL_ID Rule 2개 AI 2개
	// 토탈 MIL_ID 이미지 버퍼 6개 할당

	motor.init();
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
		bmp.LoadBitmap(IDB_BG);
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
	even_detection.model_init("./det_0528_1132_best.saigedet");
	odd_detection.model_init("./det_0528_1555_odd_best.saigedet");


	//MIL Allocation & Display Connect
	m_classMil.Allocation(0);
	m_classMil.Alloc_MIL_ImageBuffer();

	MdispSelectWindow(m_classMil.OddImageDisplay, m_classMil.OddImage, m_CtrlDisp0.GetSafeHwnd());
	MdispSelectWindow(m_classMil.EvenImageDisplay, m_classMil.EvenImage, m_CtrlDisp1.GetSafeHwnd());
	MdispSelectWindow(m_classMil.OddDisplayAI, m_classMil.OddImageAI, m_CtrlDisp2.GetSafeHwnd());
	MdispSelectWindow(m_classMil.EvenDisplayAI, m_classMil.EvenImageAI, m_CtrlDisp3.GetSafeHwnd());
	MdispSelectWindow(m_classMil.OddDisplayRule, m_classMil.OddImageRule, m_CtrlDisp4.GetSafeHwnd());
	MdispSelectWindow(m_classMil.EvenDisplayRule, m_classMil.EvenImageRule, m_CtrlDisp5.GetSafeHwnd());

}

void CKWBaseFormDlg::OnBnClickedBtnSave() // Inpsection Start
{
	motor.move_once(90, 350, 208, 900);
	m_classMil.CAM1.imgSaved = false;
	m_classMil.GrabProcess_Line2();
	//-> SAVE ORIGIN

	while (true) {
		Sleep(100);
		if (m_classMil.CAM1.imgSaved == true) {

			MdigHalt(m_classMil.CAM1.MilDigit);

			Mat image = imread(".\\Image\\origin.bmp");
			if (image.empty()) {
				cout << "이미지를 불러올 수 없습니다." << endl;
			}

			// 이미지의 높이와 너비 가져오기
			int height = image.rows; // 7000
			int width = image.cols; // 4096

			cout << "W : " << width << " / H : " << height << endl;


			Size newSize(width, height / 2); // 4096 , 3500

			// 홀수 픽셀과 짝수 픽셀을 저장할 빈 캔버스 생성
			Mat odd_pixel_canvas = Mat::zeros(newSize, image.type());
			Mat even_pixel_canvas = Mat::zeros(newSize, image.type());
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

			// 결과 이미지 저장

			Scalar s1 = mean(odd_pixel_canvas);
			Scalar s2 = mean(even_pixel_canvas);

			if (s1[0] < s2[0])
			{
				Mat temp;
				temp = odd_pixel_canvas;

				odd_pixel_canvas = even_pixel_canvas;

				even_pixel_canvas = temp;
			}

			imwrite(".\\Image\\Origin_Odd_Y.bmp", odd_pixel_canvas);
			imwrite(".\\Image\\Origin_Even_Y.bmp", even_pixel_canvas);

			//cout << "완료 " << endl;

			//MbufPutColor2d(OddImage);
			MbufPutColor2d(m_classMil.OddImage, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, width, height / 2, odd_pixel_canvas.data);
			MbufPutColor2d(m_classMil.EvenImage, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, width, height / 2, even_pixel_canvas.data);
			
			Mat result_image_even = even_detection.run_detection(".\\Image\\Origin_Even_Y.bmp");
			Mat result_image_odd = odd_detection.run_detection(".\\Image\\Origin_Odd_Y.bmp");
			imwrite(".\\Image\\AI_EVEN_Y.bmp", result_image_even);
			imwrite(".\\Image\\AI_ODD_Y.bmp", result_image_odd);
			MbufPutColor2d(m_classMil.EvenImageRule, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, width, height / 2, result_image_even.data);
			MbufPutColor2d(m_classMil.OddImageRule, M_PACKED + M_BGR24, M_ALL_BANDS, 0, 0, width, height / 2, result_image_odd.data);

			break;
		}
		
	}
	
}
