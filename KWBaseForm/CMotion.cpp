#include "pch.h"
#include "CMotion.h"

CMotion::CMotion()
{
	m_lAxisNo = 0;					// ������ �� ��ȣ
	m_lAxisCount = 0;				// ��ȿ�� ��ü ������
	m_dwModuleID = 0;				// ������ ���� ��ID

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
	//++ AXL(AjineXtek Library)�� ��밡���ϰ� �ϰ� ������ ������� �ʱ�ȭ�մϴ�.
	if ((AxlOpen(7) != AXT_RT_SUCCESS)) {
		AfxMessageBox(_T("AxlOpen Fail..."));
		return FALSE;
	}

	// �� [CAUTION] �Ʒ��� �ٸ� Mot����(��� ��������)�� ����� ��� ��θ� �����Ͻʽÿ�.
	char szFilePath[] = ".\\Recipe\\20180515ajin.mot";

	//++ ������ Mot������ ��������� ��Ǻ����� ���������� �ϰ����� �����մϴ�.
	if (AxmMotLoadParaAll(szFilePath) != AXT_RT_SUCCESS) {
		AfxMessageBox(_T("Mot File Not Found."));
	}
	return 0;
}

int CMotion::Free(int type, int num)
{

	if (m_iFlagServoOn)
		AxmSignalServoOn(m_lAxisNo, 0);

	//++ AXL ����� �����մϴ�.
	AxlClose();

	return 0;
}


int CMotion::ResetAlram(int type, int num)
{
	return 0;
}


int CMotion::Home(int type, int num)
{
	//++ ������ �࿡ �����˻��� �����մϴ�.
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
	//++ ���� ���� Servo On/Off ��ȣ�� ����մϴ�.
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
	//++ ������ ���� ������ �Ÿ�(�Ǵ� ��ġ)/�ӵ�/���ӵ�/���ӵ��� ��Ǳ����ϰ� ��� ���Ῡ�ο� ������� �Լ��� �������ɴϴ�.
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

	//++ ������ ���� ������ �Ÿ�(�Ǵ� ��ġ)/�ӵ�/���ӵ�/���ӵ��� ��Ǳ����ϰ� ��� ���Ῡ�ο� ������� �Լ��� �������ɴϴ�.
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

	//++ ������ ���� ������ �Ÿ�(�Ǵ� ��ġ)/�ӵ�/���ӵ�/���ӵ��� ��Ǳ����ϰ� ��� ���Ῡ�ο� ������� �Լ��� �������ɴϴ�.
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
		//++ ������ ���� (+)�������� ������ �ӵ�/���ӵ�/���ӵ��� ��Ǳ����մϴ�.
		dwRetCode = AxmMoveVel(m_lAxisNo, dJogVel, dJogAcc, dJogDec);
		if (dwRetCode != AXT_RT_SUCCESS) {
			strData.Format(_T("AxmMoveVel return error[Code:%04d]"), dwRetCode);
			//MessageBox(strData, "Error", MB_OK | MB_ICONERROR);
		}
		break;

	case 1017:
		//++ ������ ���� (-)�������� ������ �ӵ�/���ӵ�/���ӵ��� ��Ǳ����մϴ�.
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
	//++ ������ ���� Jog����(��Ǳ���/�����˻�����)�� ���������մϴ�.
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
// >> RepeatThread(...) : ������ ��Ʈ�ѿ� �����Ǿ� �ִ� �ؽ�Ʈ�� 
//    double������ ��ȯ�Ͽ� ��ȯ�ϴ� �Լ�.
//  - Edit, Static ��Ʈ�ѿ� ������ �ؽ�Ʈ�� double������ �о�鿩 �ڵ带 ����
//    �ϰ� ������ �� �ֽ��ϴ�.
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