
// KWBaseFormDlg.h: 헤더 파일
//

#pragma once

#include "CMil.h"
#include "Motor.h"
#include "Detection.h"
#include "OverLapDetection.h"
#include <chrono>


// CKWBaseFormDlg 대화 상자
class CKWBaseFormDlg : public CDialogEx
{
// 생성입니다.
public:
	CKWBaseFormDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CMil m_classMil;


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KWBASEFORM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	Mat odd_pixel_canvas;
	Mat even_pixel_canvas;
	int height; // Grab Image Height
	int width;	// Grab Image Width
	string save_image_path_even = ".\\Image\\Origin_Even_Y.bmp";
	string save_image_path_odd = ".\\Image\\Origin_Odd_Y.bmp";

public:
	afx_msg void OnBnClickedBtnInit();
	CStatic m_CtrlDisp0;
	CStatic m_CtrlDisp1;
	CStatic m_CtrlDisp2;
	CStatic m_CtrlDisp3;
	CStatic m_CtrlDisp5;
	CBitmapButton m_ButtonSave;
	CBitmapButton m_ButtonInit;
	CBitmapButton m_ButtonTest;



	Motor motor;
	Detection even_detection; //상부조명만
	int count = 1;
	
	CStatic m_TextResult;
	afx_msg void OnBnClickedBtnSave();

	CEdit Hole_Count;
	CEdit Hole_MinSize;
	CEdit Hole_Time;
	CEdit Hole_Double;

	CEdit EvenRuleDefactCount;
	CEdit EvenRuleInspecTime;
	CEdit EvenDL_Count;
	CEdit EvenDL_Time;
	CEdit EvenDL_Score;

	CBitmap m_Bitmap;
	CImage BG_Image;
	CImage StartButtonImg;
	CImage InitButtonImg;
	CBitmapButton m_btn_zoom;
	CBitmapButton m_btn_zoomrule;
	CBitmapButton m_btn_zoomhole;
	CListBox m_ctrl_log;

	afx_msg void OnBnClickedBtnZoom();
	void str2log(CListBox* logbox, string content);
	afx_msg void OnBnClickedBtnZoomHole();
	afx_msg void OnBnClickedBtnZoomRule();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ProcessWindowMessage();
	
	
	
	void ProcessInit(); // 최초 실행시 초기화


	void ImageSplit();
	void DetectionHoleRule();
	void DetectionNumRule();
	void DetectionNumDeepLearn();
	
	void PrintHoleRule();
	void PrintNumRule();
	void PrintNumDeepLearn();
	Mat High_Frame;
	Mat Low_Frame;
	DetectionResult DL_Frame;

	std::chrono::milliseconds DetectionHoleRuleTime;
	std::chrono::milliseconds DetectionNumRuleTime;
	int DetectionHoleRule_HoleCount;
	bool DetectionHoleRule_overlap_result;
	float DetectionHoleRule_fHoleMinSize;


	bool bDetectionHoleRuleFinish;
	bool bDetectionNumRuleFinish;
	bool bDetectionNumDeepLearnFinish;

	int DetectionNumRule_Low_Def_Count;


	afx_msg void OnBnClickedBtnInspec();
	
	afx_msg void OnBnClickedBtnTest();
};
