
// KWBaseFormDlg.h: 헤더 파일
//

#pragma once

#include "CMil.h"
#include "Motor.h"
#include "Detection.h"

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
	afx_msg void OnBnClickedBtnInit();
	CStatic m_CtrlDisp0;
	CStatic m_CtrlDisp1;
	CStatic m_CtrlDisp2;
	CStatic m_CtrlDisp3;
	CStatic m_CtrlDisp4;
	CStatic m_CtrlDisp5;
	CBitmapButton m_ButtonSave;
	CBitmapButton m_ButtonInit;
	Motor motor;
	Detection even_detection; //상부조명만
	Detection odd_detection; //전체조명
	
	CStatic m_TextResult;
	afx_msg void OnBnClickedBtnSave();


	
	

	CEdit OddRuleDefactCount;
	CEdit OddRuleInspecTime;
	CEdit EvenRuleDefactCount;
	CEdit EvenRuleInspecTime;
	CEdit OddDL_Count;
	CEdit OddDL_Time;
	CEdit EvenDL_Count;
	CEdit EvenDL_Time;



	CBitmap m_Bitmap;
	CImage BG_Image;
	CImage StartButtonImg;
	CImage InitButtonImg;
};
