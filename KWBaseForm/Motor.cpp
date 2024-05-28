#include "pch.h"
#include "Motor.h"

using namespace std;

void Motor::init()
{
	//Motor Init
	DWORD dwRetCode;
	DWORD dwBusyStatus;

	//++ AXL(AjineXtek Library)�� ��밡���ϰ� �ϰ� ������ ������� �ʱ�ȭ�մϴ�.
	dwRetCode = AxlOpen(7);
	if (dwRetCode != AXT_RT_SUCCESS) {
		cout << "fail init" << endl;
		return;
	}
	if (AxlIsOpened()) {
		cout << "init success" << endl;
	}
	//++ ������ Mot������ ��������� ��Ǻ����� ���������� �ϰ����� �����մϴ�.
	if (AxmMotLoadParaAll("./20180515ajin.mot") != AXT_RT_SUCCESS) {
		cout << "mot load fail" << endl;
	}

	//++ ���� ���� Servo On/Off ��ȣ�� ����մϴ�.
	//servo on
	AxmSignalServoOn(m_lAxisNo, ENABLE);
	AxmSignalIsServoOn(m_lAxisNo, &dwRetCode);
	if (dwRetCode == ENABLE) {
		cout << "servo on success" << endl;
	}

	dwRetCode = AxmHomeSetStart(m_lAxisNo);
	if (dwRetCode != AXT_RT_SUCCESS) {
		cout << "SetStart Fail" << endl;
	}
}

void Motor::move_position(int pos, int vel, int accel)
{
	DWORD dwBusyStatus;
	DWORD dwRetCode;

	dwRetCode = AxmMoveStartPos(m_lAxisNo, pos, vel, accel, accel);
	if (dwRetCode != AXT_RT_SUCCESS) {
		printf("AxmMoveStartPos return error[Code:%04d]\n", dwRetCode);
	}
	do {
		AxmStatusReadInMotion(m_lAxisNo, &dwBusyStatus);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	} while (dwBusyStatus);
}

void Motor::move_stop()
{
}

void Motor::move_repeat(int pos1, int pos2, int vel, int accel)
{
}

void Motor::move_once_thread(Motor* motor, int pos1, int pos2, int vel, int accel)
{
	motor->move_position(pos2, vel, accel);
	motor->move_position(pos1, vel, accel);
}


void Motor::move_once(int pos1, int pos2, int vel, int accel)
{
	bool success = false;
	double now_pos;
	do {
		AxmStatusGetCmdPos(m_lAxisNo, &now_pos);
		std::cout << "now_pos : " << now_pos << std::endl;
		if (now_pos == pos1) {
			success = true;
		}
		else {
			move_position(pos1, vel, accel);
		};
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	} while (!success);

	std::thread t(move_once_thread, this, pos1, pos2, vel, accel);
	t.detach();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Motor::repeat_stop()
{
}
