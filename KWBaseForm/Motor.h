#pragma once

#include "AXL.h"
#include "AXM.h"
#include "AXHS.h"
#include "iostream"
#include <thread>
#include <chrono>
#include <atomic>

class Motor {
public:
	long m_lAxisNo = 0;
	char* motFilePath = "./20180515ajin.mot";

	void init();

	void move_position(int pos, int vel, int accel);

	void move_stop();

	void move_repeat(int pos1, int pos2, int vel, int accel);

	static void move_once_thread(Motor* motor, int pos1, int pos2, int vel, int accel);

	void move_once(int pos1, int pos2, int vel, int accel);

	void repeat_stop();
};