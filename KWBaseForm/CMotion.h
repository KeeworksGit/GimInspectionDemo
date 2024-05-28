#pragma once

#include <iostream>

#include "afxdialogex.h"

#include "AXL.h"
#include "AXM.h"
#include "AXHS.h"

UINT RepeatThread(LPVOID pFuncData);

using namespace std;

class CMotion
{
public:
	CMotion();
	~CMotion();

	long		m_lAxisNo;					// 제어할 축 번호
	long		m_lAxisCount;				// 유효한 전체 모션축수
	DWORD		m_dwModuleID;				// 선택한 축의 모델ID
	int m_iFlagServoOn;
	double	dJogVel, dJogAcc, dJogDec;
	DWORD dwRetCode;
	CString strData;
	int m_iFlagJogLeft;
	int m_iFlagJogRight;

	BOOL m_bTestActive;
	HANDLE		m_hTestThread;

	double m_dbPos1;
	double m_dbVelocity1;
	double m_dbAcceleration1;
	double m_dbDeceleration1;

	double m_dbPos2;
	double m_dbVelocity2;
	double m_dbAcceleration2;
	double m_dbDeceleration2;

	double m_dActPos = 0.0;

	bool repeat_chk0 = false;
	bool repeat_chk1 = false;

	int m_repeatcnt = 0;

	int Init(int type, int num);
	int Free(int type, int num);
	int ResetAlram(int type, int num);
	int Home(int type, int num);
	int ServoOn(int type, int num);
	int Stop(int type, int num);
	int ClearPosition(int type, int num);
	int JogPlus(int type, int num);
	int JogMinus(int type, int num);
	int Move(int type, int num, int Pos);
	int SetParam(int type, int num, int datatype, int datanum, void* pdata);
	int Move(int type, int num, double dPos, double dVelocity, double dAcceleration, double dDeceleration);
	int MovePos1(int type, int num, double dPos, double dVelocity, double dAcceleration, double dDeceleration);
	int MovePos2(int type, int num, double dPos, double dVelocity, double dAcceleration, double dDeceleration);
	int JogDown(WPARAM wParam, LPARAM lParam);
	int JogUp(WPARAM wParam, LPARAM lParam);
	int MoveRepeat(int type, int num);

	void GetActPos();
};