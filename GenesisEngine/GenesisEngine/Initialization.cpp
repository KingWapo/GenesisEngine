#include <direct.h>
#include <ShlObj.h>

#include "Initialization.h"


//
// Check Storage Space Available
//
bool CheckStorage(const DWORDLONG diskSpaceNeeded)
{
	// Check for enough free disk space on the current disk.
	int const drive = _getdrive();
	struct _diskfree_t diskfree;

	_getdiskfree(drive, &diskfree);

	unsigned __int64 const neededClusters =
		diskSpaceNeeded / (diskfree.sectors_per_cluster * diskfree.bytes_per_sector);

	if (diskfree.avail_clusters < neededClusters)
	{
		// If you get here you don't have enough space!
		GCC_ERROR("CheckStorage Failure: Not enough physical storage.");
		return false;
	}
	return true;
}

//
// Check the Memory Available
//
bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded)
{
	MEMORYSTATUSEX status;
	GlobalMemoryStatusEx(&status);
	if (status.ullTotalPhys < physicalRAMNeeded)
	{
		// you don't have enough physical memory. Tell the player to go get a real
		// computer and give this one to his mother.
		GCC_ERROR("CheckMemory Failure: Not enough physical memory.");
		return false;
	}

	//Check for enough free memory.
	if (status.ullAvailVirtual < virtualRAMNeeded)
	{
		// you don't have enough virtual memory available.
		GCC_ERROR("CheckMemory Failure: Not enough virtual memory.");
		return false;
	}

	char *buff = GCC_NEW char[(unsigned int)virtualRAMNeeded];
	if (buff)
		delete[] buff;
	else
	{
		// Even though there is enough memory, it isn't available in one
		// block, which can be critical for games that manage their own memory
		GCC_ERROR("CheckMemory Failure: Not enough contiguous available memory.");
		return false;
	}
	return true;
}

//
// Read the CPU Speed
//
DWORD ReadCPUSpeed()
{
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;

	// open the key where the proc speed is hidden:
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
		0, KEY_READ, &hKey);

	if (lError == ERROR_SUCCESS)
	{
		// Query the key:
		RegQueryValueEx(hKey, L"~MHz", NULL, &type, (LPBYTE)&dwMHz, &BufSize);
	}
	return dwMHz;
}

GameOptions::GameOptions()
{
	// set all the options to decent default values
	m_Level = "";
	m_Renderer = "OpenGL"; // Check version?
	m_runFullSpeed = false;
	m_ScreenSize = Point(1024, 768);
	m_useDevelopmentDirectories = false;
}

//
// Check if this is the only instance of the game.
//
bool IsOnlyInstance(LPCTSTR gameTitle)
{
	// Find the window. If active, set and return false
	// Only one game instance may have this mutex at a time...

	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);

	if (GetLastError() != ERROR_SUCCESS)
	{
		HWND hWnd = FindWindow(gameTitle, NULL);
		if (hWnd)
		{
			// An instance of your game is already running.
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
			return false;
		}
	}
	return true;
}

//
// Get the Save Game Directory for the game
//
const TCHAR *GetSaveGameDirectory(HWND hWnd, const TCHAR *gameAppDirectory)
{
	HRESULT hr;
	static TCHAR m_SaveGameDirectory[MAX_PATH];
	TCHAR userDataPath[MAX_PATH];

	hr = SHGetSpecialFolderPath(hWnd, userDataPath, CSIDL_APPDATA, true);

	_tcscpy_s(m_SaveGameDirectory, userDataPath);
	_tcscat_s(m_SaveGameDirectory, _T("\\"));
	_tcscat_s(m_SaveGameDirectory, gameAppDirectory);

	// Does our directory exist?
	if (0xffffffff == GetFileAttributes(m_SaveGameDirectory))
	{
		if (SHCreateDirectoryEx(hWnd, m_SaveGameDirectory, NULL) != ERROR_SUCCESS)
			return false;
	}

	_tcscat_s(m_SaveGameDirectory, _T("\\"));

	return m_SaveGameDirectory;
}

//
// Check for any Joysticks
//
bool CheckForJoystick(HWND hWnd)
{
	JOYINFO joyinfo;
	UINT wNumDevs;
	BOOL bDev1Attached, bDev2Attached;
	/*
	if ((wNumDevs = joyGetNumDevs()) == 0)
		return false;
	bDev1Attached = joyGetPos(JOYSTICKID1, &joyinfo) != JOYERR_UNPLUGGED;
	bDev2Attached = joyGetPos(JOYSTICKID2, &joyinfo) != JOYERR_UNPLUGGED;
	if (bDev1Attached)
		joySetCapture(hWnd, JOYSTICKID1, 1000 / 30, true);
	if (bDev2Attached)
		joySetCapture(hWnd, JOYSTICKID2, 1000 / 30, true);
		
	return true;
	*/
	return false;
}