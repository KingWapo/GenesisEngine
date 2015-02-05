#pragma once

// #include "Includes.h"
#include "Types.h"

extern bool CheckStorage(const DWORDLONG diskSpaceNeeded);
extern DWORD ReadCPUSpeed();
extern bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
extern bool IsOnlyInstance(LPCTSTR gameTitle);
extern const TCHAR *GetSaveGameDirectory(HWND hWnd, const TCHAR *gameAppDirectory);
extern bool CheckForJoystick(HWND hWnd);

struct GameOptions
{
	// Level option
	std::string m_Level;

	// Rendering options
	std::string m_Renderer;
	bool m_runFullSpeed;
	Point m_ScreenSize;

	// Resource Cache Options
	bool m_useDevelopmentDirectories;

	GameOptions();
	~GameOptions() { };
};

