#include "pch.h"
#include "CMotion.h"

CMotion::CMotion()
{
	m_lAxisNo = 0;					// 제어할 축 번호
	m_lAxisCount = 0;				// 유효한 전체 모션축수
	m_dwModuleID = 0;				// 선택한 축의 모델ID

	m_iFlagServoOn = 0;

	dJogVel = 200;
	dJogAcc = 200;
	dJogDec = 200;


	m_dbPos1 = 0.0;
	m_dbVelocity1 = 0.0;
	m_dbAcceleration1 = 0.0;
	m_dbDeceleration1 = 0.0;

	m_dbPos2 = 0.0;
	m_dbVelocity2 = 0.0;
	m_dbAcceleration2 = 0.0;
	m_dbDeceleration2 = 0.0;
}

CMotion::~CMotion()
{

}

int CMotion::Init(int type, int num)
{
	//++ AXL(AjineXtek Library)을 사용가능하게 하고 장착된 보드들을 초기화합니다.
	if ((AxlOpen(7) != AXT_RT_SUCCESS)) {
		AfxMessageBox(_T("AxlOpen Fail..."));
		return FALSE;
	}

	// ※ [CAUTION] 아래와 다른 Mot파일(모션 설정파일)을 사용할 경우 경로를 변경하십시요.
	char szFilePath[] = ".\\Recipe\\20180515ajin.mot";

	//++ 지정한 Mot파일의 설정값들로 모션보드의 설정값들을 일괄변경 적용합니다.
	if (AxmMotLoadParaAll(szFilePath) != AXT_RT_SUCCESS) {
		AfxMessageBox(_T("Mot File Not Found."));
	}
	return 0;
}

int CMotion::Free(int type, int num)
{

	if (m_iFlagServoOn)
		AxmSignalServoOn(m_lAxisNo, 0);

	//++ AXL 사용을 종료합니다.
	AxlClose();

	return 0;
}


int CMotion::ResetAlram(int type, int num)
{
	return 0;
}


int CMotion::Home(int type, int num)
{
	//++ 지정한 축에 원점검색을 진행합니다.
	dwRetCode = AxmHomeSetStart(m_lAxisNo);
	if (dwRetCode != AXT_RT_SUCCESS) {
		CString strData;
		strData.Format(_T("AxmHomeSetStart return error[Code:%04d]"), dwRetCode);
		//MessageBox(strData, "Error", MB_OK | MB_ICONERROR);
	}
	return 0;
}


int CMotion::ServoOn(int type, int num)
{
	//++ 지정 축의 Servo On/Off 신호를 출력합니다.
	if (m_iFlagServoOn)
		m_iFlagServoOn = FALSE;
	else
		m_iFlagServoOn = TRUE;

	AxmSignalServoOn(m_lAxisNo, m_iFlagServoOn);
	return 0;
}


int CMotion::Stop(int type, int num)
{
	dwRetCode = AxmMoveSStop(m_lAxisNo);
	m_bTestActive = FALSE;
	if (dwRetCode != AXT_RT_SUCCESS)
	{
		strData.Format(_T("AxmMoveSStop return error[Code:%04d]"), dwRetCode);
		//MessageBox(strData, "Error", MB_OK | MB_ICONERROR);
	}
	return 0;
}


int CMotion::ClearPosition(int type, int num)
{
	return 0;
}


int CMotion::JogPlus(int type, int num)
{
	dwRetCode = AxmMoveVel(m_lAxisNo, dJogVel, dJogAcc, dJogDec);
	if (dwRetCode != AXT_RT_SUCCESS) {
		strData.Format(_T("AxmMoveVel return error[Code:%04d]"), dwRetCode);
		//MessageBox(strData, "Error", MB_OK | MB_ICONERROR);
	}
	return 0;
}


int CMotion::JogMinus(int type, int num)
{
	dwRetCode = AxmMoveVel(m_lAxisNo, -dJogVel, dJogAcc, dJogDec);
	if (dwRetCode != AXT_RT_SUCCESS) {
		strData.Format(_T("AxmMoveVel return error[Code:%04d]"), dwRetCode);
		//MessageBox(strData, "Error", MB_OK | MB_ICONERROR);
	}
	return 0;
}


int CMotion::Move(int type, int num, int Pos)
{

	return 0;
}


int CMotion::SetParam(int type, int num, int datatype, int datanum, void* pdata)
{
	return 0;
}


int CMotion::Move(int type, int num, double dPos, double dVelocity, double dAcceleration, double dDeceleration)
{
	//++ 지정한 축을 지정한 거리(또는 위치)/속도/가속도/감속도로 모션구동하고 모션 종료여부와 상관없이 함수를 빠져나옵니다.
	dwRetCode = AxmMoveStartPos(m_lAxisNo, dPos, dVelocity, dAcceleration, dDeceleration);
	if (dwRetCode != AXT_RT_SUCCESS) {
		strData.Format(_T("AxmMoveStartPos return error[Code:%04d]"), dwRetCode);
		//MessageBox(strData, "Error", MB_OK | MB_ICONERROR);
	}
	return 0;
}


int CMotion::MovePos1(int type, int num, double dPos, double dVelocity, double dAcceleration, double dDeceleration)
{
	m_dbPos1 = dPos;
	m_dbVelocity1 = dVelocity;
	m_dbAcceleration1 = dAcceleration;
	m_dbDeceleration1 = dDeceleration;

	//++ 지정한 축을 지정한 거리(또는 위치)/속도/가속도/감속도로 모션구동하고 모션 종료여부와 상관없이 함수를 빠져나옵니다.
	dwRetCode = AxmMoveStartPos(m_lAxisNo, m_dbPos1, m_dbVelocity1, m_dbAcceleration1, m_dbDeceleration1);
	if (dwRetCode != AXT_RT_SUCCESS) {
		strData.Format(_T("AxmMoveStartPos return error[Code:%04d]"), dwRetCode);
		//MessageBox(strData, "Error", MB_OK | MB_ICONERROR);
	}
	return 0;
}


int CMotion::MovePos2(int type, int num, double dPos, double dVelocity, double dAcceleration, double dDeceleration)
{
	m_dbPos2 = dPos;
	m_dbVelocity2 = dVelocity;
	m_dbAcceleration2 = dAcceleration;
	m_dbDeceleration2 = dDeceleration;

	//++ 지정한 축을 지정한 거리(또는 위치)/속도/가속도/감속도로 모션구동하고 모션 종료여부와 상관없이 함수를 빠져나옵니다.
	dwRetCode = AxmMoveStartPos(m_lAxisNo, m_dbPos2, m_dbVelocity2, m_dbAcceleration2, m_dbDeceleration2);
	if (dwRetCode != AXT_RT_SUCCESS) {
		strData.Format(_T("AxmMoveStartPos return error[Code:%04d]"), dwRetCode);
		//MessageBox(strData, "Error", MB_OK | MB_ICONERROR);
	}
	return 0;
}

int CMotion::JogDown(WPARAM wParam, LPARAM lParam)
{
	DWORD dwRetCode;

	switch (wParam)
	{
	case 1016:
		//++ 지정한 축을 (+)방향으로 지정한 속도/가속도/감속도로 모션구동합니다.
		dwRetCode = AxmMoveVel(m_lAxisNo, dJogVel, dJogAcc, dJogDec);
		if (dwRetCode != AXT_RT_SUCCESS) {
			strData.Format(_T("AxmMoveVel return error[Code:%04d]"), dwRetCode);
			//MessageBox(strData, "Error", MB_OK | MB_ICONERROR);
		}
		break;

	case 1017:
		//++ 지정한 축을 (-)방향으로 지정한 속도/가속도/감속도로 모션구동합니다.
		dwRetCode = AxmMoveVel(m_lAxisNo, -dJogVel, dJogAcc, dJogDec);
		if (dwRetCode != AXT_RT_SUCCESS) {
			strData.Format(_T("AxmMoveVel return error[Code:%04d]"), dwRetCode);
			//MessageBox(strData, "Error", MB_OK | MB_ICONERROR);
		}
		break;
	}
	return 0;
}


int CMotion::JogUp(WPARAM wParam, LPARAM lParam)
{
	//++ 지정한 축의 Jog구동(모션구동/원점검색구동)을 감속정지합니다.
	AxmMoveSStop(m_lAxisNo);
	return 0;
}


int CMotion::MoveRepeat(int type, int num)
{
	unsigned long	ThreadID;

	if (!m_bTestActive)
	{
		m_bTestActive = TRUE;
		if (m_hTestThread == NULL)
			m_hTestThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RepeatThread, this, NULL, &ThreadID);
	}
	else
	{
		m_bTestActive = FALSE;
	}
	return 0;
}

void CMotion::GetActPos()
{
	AxmStatusGetActPos(m_lAxisNo, &m_dActPos);
}

// ++ =======================================================================
// >> RepeatThread(...) : 지정한 콘트롤에 설정되어 있는 텍스트를 
//    double값으로 변환하여 반환하는 함수.
//  - Edit, Static 콘트롤에 설정된 텍스트를 double값으로 읽어들여 코드를 간결
//    하게 구현할 수 있습니다.
// --------------------------------------------------------------------------
UINT RepeatThread(LPVOID pFuncData)
{
	TRACE("Thread\n");
	double	dCurPos;
	DWORD	dwMode;
	DWORD	dwBusyStatus;

	CMotion* pQI = (CMotion*)pFuncData;

	int nCurSel = 0;

	double dPosition, dVelocity, dAccel, dDecel;

	dPosition = pQI->m_dbPos2;
	dVelocity = pQI->m_dbVelocity2;
	dAccel = pQI->m_dbAcceleration2;
	dDecel = pQI->m_dbDeceleration2;

	AxmMotGetAbsRelMode(nCurSel, &dwMode);
	AxmStatusGetCmdPos(nCurSel, &dCurPos);

	// Re-setup of the maximum value in chart for displaying running speed of each axis on the chart.
	while (pQI->m_bTestActive)
	{
		AxmMoveStartPos(nCurSel, dPosition, dVelocity, dAccel, dAccel);
		do {
			AxmStatusReadInMotion(nCurSel, &dwBusyStatus);
			Sleep(100);
		} while ((pQI->m_bTestActive) && dwBusyStatus);

		if (!pQI->m_bTestActive)	break;

		if (dwMode == POS_ABS_MODE) {
			if (dCurPos == dPosition)		break;
			AxmMoveStartPos(nCurSel, dCurPos, dVelocity, dAccel, dAccel);
		}
		else {
			if (0 == dPosition)				break;
			AxmMoveStartPos(nCurSel, -dPosition, dVelocity, dAccel, dAccel);
		}

		do {
			AxmStatusReadInMotion(nCurSel, &dwBusyStatus);
			Sleep(1);
		} while ((pQI->m_bTestActive) && dwBusyStatus);

		pQI->m_repeatcnt++;



	}

	pQI->m_bTestActive = FALSE;
	CloseHandle(pQI->m_hTestThread);
	pQI->m_hTestThread = NULL;

	return 0;
}