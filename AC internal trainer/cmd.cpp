#include "pch.h"
#include "cmd.h"
#include <Windows.h>
#include <iostream>

void cmd::ShowCmd()
{
	ShowWindow(GetConsoleWindow(), 0x5);
}

void cmd::HideCmd()
{
	ShowWindow(GetConsoleWindow(), 0x0);
}

BOOL cmd::IsCmdVisble()
{
	return IsWindowVisible(GetConsoleWindow());
}

FILE* cmd::CreateCmd()
{
	FILE* f;

	AllocConsole();

	freopen_s(&f, "CONOUT$", "w", stdout);

	return f;
}

void cmd::CloseCmd(FILE* f)
{
	fclose(f);
	FreeConsole();
}

BOOL cmd::ResizeCmd()
{
	if (cmd::IsCmdVisble())
	{
		SMALL_RECT newSize;
		newSize.Left = 20;
		newSize.Top = 40;
		newSize.Bottom = newSize.Top;
		newSize.Right = newSize.Left;

		return SetConsoleWindowInfo(GetConsoleWindow(), true, &newSize);
	}
	return true;
}
