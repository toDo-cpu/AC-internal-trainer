#pragma once
#include <Windows.h>
#include <iostream>

namespace cmd {

	void ShowCmd();

	void HideCmd();

	BOOL IsCmdVisble();

	FILE* CreateCmd();

	void CloseCmd(FILE* f);
}

