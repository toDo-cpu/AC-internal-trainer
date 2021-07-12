#pragma once
#include <Windows.h>
#include <iostream>

namespace cmd {

	void ShowCmd();

	void HideCmd();

	BOOL IsCmdVisble();

	FILE* CreateCmd();

	BOOL ResizeCmd();

	void CloseCmd(FILE* f);
}

