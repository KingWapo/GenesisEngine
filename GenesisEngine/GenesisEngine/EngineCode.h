#pragma once

//#include "Initialization.h"
#include "BaseGameLogic.h"
#include "Initialization.h"
#include "Math.h"
#include "Window.h"

#include <mmsystem.h>

// Several classes that may be needed in the future:
class FontHandler;
class BaseUI;
class EventManager;
class HumanView;

//
// Basic App
//
class EngineApp
{
protected:

	HWND m_hWnd;
	HINSTANCE m_hInstance;			// the module instance
	bool m_bWindowedMode;			// true if the app is windowed, false if fullscreen
	bool m_bIsRunning;				// true if everything is initialized and the game is in the main loop
	bool m_bQuitRequested;			// true if the app should run the exit sequence
	bool m_bQuitting;				// true if the app is running the exit sequence
	Rect m_rcDesktop;				// current desktop size - not necessarily the client window size
	Point m_screenSize;				// game screen size
	int m_iColorDepth;				// current color depth (16 or 32)
	bool m_bIsEditorRunning;		// true if the game editor is running

	// OpenGl window
	Window m_window;

protected:
	std::map<std::wstring, std::wstring> m_textResource;
	std::map<std::wstring, UINT> m_hotkeys;

	int m_HasModalDialog;			// Determines if a modal dialog is up
	int PumpUntilMessage(UINT msgEnd, WPARAM *pWParam, LPARAM *pLParam);
	int EatSpecificMessages(UINT msgType, optional<LPARAM> lParam, optional<WPARAM> wParam);
	void FlashWhileMinimized();

public:
	const Point &GetScreenSize() { return m_screenSize; }

	EngineApp();

	// Game Application Data
	// You must define these in an inherited
	// class
	virtual TCHAR *VGetGameTitle() = 0;
	virtual TCHAR *VGetGameAppDirectory() = 0;
	virtual HICON VGetIcon() = 0;

	// Win32 Specific Stuff
	HWND GetHwnd();
	HINSTANCE GetInstance() { return m_hInstance; }
	virtual bool InitInstance(int screenWidth = SCREEN_WIDTH, int screenHeight = SCREEN_HEIGHT);
	virtual bool InitInstance(HINSTANCE hInstance, LPWSTR lpCmdLine, HWND hWnd = NULL, int screenWidth = SCREEN_WIDTH, int screenHeight = SCREEN_HEIGHT);

	static LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool *pbNoFurtherProcessing, void *pUserContext);
	bool HasModalDialog() { return m_HasModalDialog != 0; }
	//void ForceModalExit() { PostMessage(GetHwnd(), g_MsgEndModal, 0, g_QuitNoPrompt); } // g_* in UserInterface.h

	LRESULT OnDisplayChange(int colorDepth, int width, int height);
	LRESULT OnPowerBroadcast(int event);
	LRESULT OnSysCommand(WPARAM wParam, LPARAM lParam);
	LRESULT OnClose();

	// Game Application Actions
	LRESULT OnAltEnter();
	LRESULT OnNcCreate(LPCREATESTRUCT cs);

	bool LoadStrings(std::string language);
	std::wstring GetString(std::wstring sID);
	int GethotKeyForString(std::wstring sID);
	UINT MapCharToKeycode(const char pHotkey);

	int Modal(std::tr1::shared_ptr<IScreenElement> pModalScreen, int defaultAnswer);

	// Render functions
	
	static void CALLBACK OnUpdateGame(double fTime, float fElapsedTime, void *pUserContext);

	//BaseGameLogic and GameOptions
	BaseGameLogic *m_pGame;
	struct GameOptions m_Options;

	virtual BaseGameLogic *VCreateGameAndView() = 0;
	virtual bool VLoadGame(void);
	HumanView* GetHumanView();

	// File and Resource System
	class ResCache *m_ResCache;
	TCHAR m_saveGameDirectory[MAX_PATH];

	bool IsEditorRunning() { return m_bIsEditorRunning; }

	// Event manager

	// Socket Manager

	// Networking

	void AbortGame() { m_bQuitting = true; }
	int GetExitCode() { return 0; }
	bool IsRunning() { return m_bIsRunning; }
	void SetQuitting(bool quitting) { m_bQuitting = quitting; }

	// Base Game Logic

protected:
	virtual void VRegisterGameEvents(void) {}

private:
	void RegisterEngineEvents(void);

};


extern EngineApp *g_pApp;