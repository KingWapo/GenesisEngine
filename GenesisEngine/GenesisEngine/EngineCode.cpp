#include "EngineCode.h"
#include "Initialization.h"
#include "UserInterface.h"
#include "MessageBox.h"
#include "TestGame.h"

#define MAX_LOADSTRING 100

EngineApp *g_pApp = NULL;

static TCHAR szWindowClass[] = _T("win32app");
static TCHAR szTitle[] = _T("Genesis Engine");

// Pre init lua file for script mana
//const char *SCRIPT_PREINIT_FILE = "Scripts\\PreInit.lua";

//========================================================================
//
// EngineApp implementation
//
//========================================================================
EngineApp::EngineApp()
{
	g_pApp = this;
	m_pGame = NULL;

	m_rcDesktop.bottom = 0;
	m_rcDesktop.left = 0;
	m_rcDesktop.right = 0;
	m_rcDesktop.top = 0;
	m_screenSize = Point(0, 0);
	m_iColorDepth = 32;

	m_bIsRunning = false;
	m_bIsEditorRunning = false;

	// Event manager
	// Res Cache

	// Network Handler

	m_bQuitRequested = false;
	m_bQuitting = false;
	m_HasModalDialog = 0;
}

HWND EngineApp::GetHwnd()
{
	return m_hWnd;
}

bool EngineApp::InitInstance(HINSTANCE hInstance, LPWSTR lpCmdLine, HWND hWnd, int screenWidth, int screenHeight)
{
	return InitInstance(screenWidth, screenHeight);
}

bool EngineApp::InitInstance(/*HINSTANCE hInstance, LPWSTR lpCmdLine, HWND hWnd,*/ int screenWidth, int screenHeight)
{
	// Check for existing instance of the same window
#ifndef _DEBUG
	// Note - it can be really useful to debug network code to have
	// more than one instance of the game up at one time
	if (!IsOnlyInstance(VGetGameTitle()))
		return false;
#endif
	// We don't need a mouse cursor by default, let the game turn it on
	SetCursor(NULL);

	// Check for adequate machine resources.
	bool resourceCheck = false;
	while (!resourceCheck)
	{
		const DWORDLONG physicalRAM = 512 * MEGABYTE;
		const DWORDLONG virtualRAM = 1024 * MEGABYTE;
		const DWORDLONG diskSpace = 10 * MEGABYTE;
		if (!CheckStorage(diskSpace))
			return false;

		const DWORD minCpuSpeed = 1300;
		DWORD thisCPU = ReadCPUSpeed();
		if (thisCPU < minCpuSpeed)
		{
			GCC_ERROR("GetCPUSpeed reports CPU is too slow for this game.");
			return false;
		}

		resourceCheck = true;
	}

	//m_hInstance = hInstance;

	// Register all events
	RegisterEngineEvents();
	VRegisterGameEvents();

	// Initialize the ResCache

	extern shared_ptr<IResourceLoader> CreateWAVResourceLoader();
	extern shared_ptr<IResourceLoader> CreateOGGResourceLoader();
	extern shared_ptr<IResourceLoader> CreateDDSResourceLoader();
	extern shared_ptr<IResourceLoader> CreateJPGResourceLoader();
	extern shared_ptr<IResourceLoader> CreateXmlResourceLoader();
	extern shared_ptr<IResourceLoader> CreateSdkMeshResourceLoader();
	extern shared_ptr<IResourceLoader> CreateScriptResourceLoader();

	// Register from least to most important
	// Register the m_ResCache

	// Load strings

	// Lua Script Manager

	// Event Manager

	// Create Window
	//m_window = Window();
	//m_window.create("Genesis Engine", screenWidth, screenHeight, SDL_WINDOW_OPENGL);



	// initialize the directory location you can store save game files
	_tcscpy_s(m_saveGameDirectory, GetSaveGameDirectory(GetHwnd(), VGetGameAppDirectory()));

	m_screenSize = Point(screenWidth, screenHeight);

	// Create Device?

	// VCreateGameAndView
	// Create Game
	if (!m_pGame)
		return false;

	// Preload.

	CheckForJoystick(GetHwnd());
	
	m_bIsRunning = true;

	return TRUE;
}



bool EngineApp::VLoadGame(void)
{
	// Read the game options and see what the current game
	// needs to be - all of the game graphics are initialized by now, too
	return m_pGame->VLoadGame("m_Options.m_Level.c_str()");
}



void EngineApp::RegisterEngineEvents(void)
{
	// Register Events...
}

//Load strings
bool EngineApp::LoadStrings(std::string language)
{
	//xml stuff
	return true;
}

UINT EngineApp::MapCharToKeycode(const char pHotKey)
{
	if (pHotKey >= '0' && pHotKey <= '9')
		return 0x30 + pHotKey - '0';

	if (pHotKey >= 'A' && pHotKey <= 'Z')
		return 0x41 + pHotKey - 'A';

	GCC_ASSERT(0 && "Platform specific hotkey is not defined.");
	return 0;
}

// GetString -- Creates a string from a string resource ID in the
// string table stored in a special DLL, LANG.DLL, so game text
// strings can be language independent
std::wstring EngineApp::GetString(std::wstring sID)
{
	auto localizedString = m_textResource.find(sID);
	if (localizedString == m_textResource.end())
	{
		GCC_ASSERT(0 && "String not found!");
		return L"";
	}
	return localizedString->second;
}


//----------------------------------------------------------
// Win32 Specific Message Handlers
//
// WndProc - the main message handler for the window class
//
// OnNcCreate - this is where you can set window data before it is created
// OnMove - called whenever the window moves; used to update members of g_App
// OnDeviceChange - called whenever you eject the CD-ROM.
// OnDisplayChange - called whenever the user changes the desktop settings
// OnPowerBroadcast - called whenever a power message forces a shutdown
// OnActivate - called whenever windows on the desktop change focus.
//
// Note: pUserContext added to comply with DirectX 9c - June 2005 Update
//
LRESULT CALLBACK EngineApp::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	// Always allow dialog resource manager calls to handle global messages
	// so GUI state is updated correctly
	//*pbNoFurtherProcessing = D3DRenderer::g_DialogResourceManager.MsgProc(hWnd, uMsg, wParam, lParam);
	//if (*pbNoFurtherProcessing)
	//	return 0;

	LRESULT result = 0;

	switch (uMsg)
	{
	case WM_POWERBROADCAST:
	{
							  int event = (int)wParam;
							  result = g_pApp->OnPowerBroadcast(event);
							  break;
	}

	case WM_DISPLAYCHANGE:
	{
							 int colorDepth = (int)wParam;
							 int width = (int)(short)LOWORD(lParam);
							 int height = (int)(short)HIWORD(lParam);

							 result = g_pApp->OnDisplayChange(colorDepth, width, height);
							 break;
	}

	case WM_SYSCOMMAND:
	{
						  result = g_pApp->OnSysCommand(wParam, lParam);
						  if (result)
						  {
							  *pbNoFurtherProcessing = true;
						  }
						  break;
	}

	case WM_SYSKEYDOWN:
	{
						  if (wParam == VK_RETURN)
						  {
							  *pbNoFurtherProcessing = true;
							  return g_pApp->OnAltEnter();
						  }
						  return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}


	case WM_CLOSE:
	{
					 // DXUT apps choose ESC key as a default exit command.
					 // GameCode4 doesn't like this so we disable it by checking 
					 // the m_bQuitting bool, and if we're not really quitting
					 // set the "no further processing" parameter to true.
					 if (g_pApp->m_bQuitting)
					 {
						 result = g_pApp->OnClose();
					 }
					 else
					 {
						 *pbNoFurtherProcessing = true;
					 }
					 break;
	}


	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case MM_JOY1BUTTONDOWN:
	case MM_JOY1BUTTONUP:
	case MM_JOY1MOVE:
	case MM_JOY1ZMOVE:
	case MM_JOY2BUTTONDOWN:
	case MM_JOY2BUTTONUP:
	case MM_JOY2MOVE:
	case MM_JOY2ZMOVE:
	{
						 
						 if (g_pApp->m_pGame)
						 {
							 BaseGameLogic *pGame = g_pApp->m_pGame;
							 // Note the reverse order! User input is grabbed first from the view that is on top, 
							 // which is the last one in the list.
							 AppMsg msg;
							 msg.m_hWnd = hWnd;
							 msg.m_uMsg = uMsg;
							 msg.m_wParam = wParam;
							 msg.m_lParam = lParam;
							 for (GameViewList::reverse_iterator i = pGame->m_gameViews.rbegin(); i != pGame->m_gameViews.rend(); ++i)
							 {
								 if ((*i)->VOnMsgProc(msg))
								 {
									 result = true;
									 break;				// WARNING! This breaks out of the for loop.
								 }
							 }
						 }
						 break;
	}

		/**********************
		WARNING!!!!! You MIGHT think you need this, but if you use the DirectX
		Framework the DefWindowProc is called for you....

		default:
		return DefWindowProc(hWnd, message, wParam, lParam);

		***********************/
	}

	return result;
}

// EngineApp::OnNcCreate
// Handles the WM_NCCREATE message
LRESULT EngineApp::OnNcCreate(LPCREATESTRUCT cs)
{
	// If you want to override something in the CREATESTRUCT
	// do it here! (Change window borders, etc.)
	return true;
}

// EngineApp::OnDisplayChange
// Handles the WM_DISPLAYCHANGE message
LRESULT EngineApp::OnDisplayChange(int colorDepth, int width, int height)
{
	m_rcDesktop.left = 0;
	m_rcDesktop.top = 0;
	m_rcDesktop.right = width;
	m_rcDesktop.bottom = height;
	m_iColorDepth = colorDepth;
	return 0;
}

// EngineApp::OnPowerBroadcast
// Handles the WM_POWERBROADCAST message
LRESULT EngineApp::OnPowerBroadcast(int event)
{
	// Don't allow the game to go into sleep mode
	if (event == PBT_APMQUERYSUSPEND)
		return BROADCAST_QUERY_DENY;
	else if (event == PBT_APMBATTERYLOW)
	{
		AbortGame();
	}

	return true;
}

// EngineApp::OnSysCommand
// Handles the WM_SYSCOMMAND message
LRESULT EngineApp::OnSysCommand(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case SC_MAXIMIZE:
		{
			// If windowed and ready....
			if (m_bWindowedMode && IsRunning())
			{
				// Make maximize into FULLSCREEN toggle
				OnAltEnter();
			}
		}
		return 0;

		case SC_CLOSE:
			// The quit dialog confirmation would appear once for
			// every SC_CLOSE we get - which happens multiple times
			// if modal dialogs are up. This now uses the g_QuitNoPrompt
			// flag to only prompt when receiving a SC_CLOSE that isn't
			// generated by us (identified by g_QuitNoPrompt).

			// If closing, promt to close if this isn't a forced quit
			if (lParam != g_QuitNoPrompt)
			{
				// Eat if already servicing a close
				if (m_bQuitRequested)
					return true;

				// Wait for the application to be restored
				// before going any further with the new
				// screen. Flash until the person selects
				// that they want to restore the game, then
				// reinit the display if fullscreen.
				// The reinit is necessary otherwise the game
				// will switch to windowed mode.

				// Quit requested
				m_bQuitRequested = true;
				// Prompt
				if (MessageBox::Ask(QUESTION_QUIT_GAME) == IDNO)
				{
					// Bail - quit aborted

					// reset quit requested flag
					m_bQuitRequested = false;
					return true;
				}
			}

			m_bQuitting = true;

			// Is there a game modal dialog up?
			if (HasModalDialog())
			{
				// Close the modal and keep posting close to the app
				// ForceModalExit();

				// Reissue the close to the app

				// Issue the new close after handling the current one,
				// but send in g_QuitNoPrompt to differentiate it from
				// a regular CLOSE issued by the system.
				PostMessage(GetHwnd(), WM_SYSCOMMAND, SC_CLOSE, g_QuitNoPrompt);

				m_bQuitRequested = false;

				// Eat the close
				return true;
			}
			// Reset the quit after any other dialogs have popped up from this close
			m_bQuitRequested = false;

			return 0;

		default:
			// Return non-zero of we didn't process the SYSCOMMAND message
			return DefWindowProc(GetHwnd(), WM_SYSCOMMAND, wParam, lParam);
	}

	return 0;
}

// EngineApp::OnClose
// Handles the WM_CLOSE message
LRESULT EngineApp::OnClose()
{
	// Release all the game systems in reverse order from which they were created

	SAFE_DELETE(m_pGame);

	DestroyWindow(GetHwnd());
	
	// Destroy Network Event Forwarder

	// Destroy Socket Manager

	// Destroy Event Manager

	// Destroy Script Manager

	SAFE_DELETE(m_ResCache);

	return 0;
}

// EngineApp::FlashWhileMinimized
//
// Wait for the application to be restored
// before going any further with the new screen.
// Flash until the person selects that they
// want to restore the game.
void EngineApp::FlashWhileMinimized()
{
	// Flash the application on the taskbar
	// until it's restored.
	if (!GetHwnd())
		return;

	// Blink the application if we are minimized,
	// waiting until we are no longer minimized
	if (IsIconic(GetHwnd()))
	{
		// Make sure the app is up when creating a new screen
		// this should be the case most of the time, but when
		// we close the app down, minimized, and a confirmation
		// dialog appears, we need to restore
		DWORD now = timeGetTime();
		DWORD then = now;
		MSG msg;

		FlashWindow(GetHwnd(), true);

		while (true)
		{
			if (PeekMessage(&msg, NULL, 0, 0, 0))
			{
				if (msg.message != WM_SYSCOMMAND || msg.wParam != SC_CLOSE)
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}

				// Are we done?
				if (!IsIconic(GetHwnd()))
				{
					FlashWindow(GetHwnd(), false);
					break;
				}
			}
			else
			{
				now = timeGetTime();
				DWORD timeSpan = now > then ? (now - then) : (then - now);
				if (timeSpan > 1000)
				{
					then = now;
					FlashWindow(GetHwnd(), true);
				}
			}
		}
	}
}

// EngineApp::OnAltEnter
// Called when the player hits Alt-Enter to flip the
// display mode.
LRESULT EngineApp::OnAltEnter()
{
	// Toggle to full screen
	return 0;
}

// EngineApp::GetHumanView() -- Not setup
HumanView* EngineApp::GetHumanView()
{
	HumanView *pView = NULL;
	for (GameViewList::iterator i = m_pGame->m_gameViews.begin(); i != m_pGame->m_gameViews.end(); ++i)
	{
		if ((*i)->VGetType() == GameView_Human)
		{
			shared_ptr<IGameView> pIGameView(*i);
			//pView = static_cast<HumanView *>(&*pIGameView); // Static Cast does not work
			break;
		}
	}
	return pView;
}

// EngineApp::Modal
int EngineApp::Modal(shared_ptr<IScreenElement> pModalScren, int defaultAnswer)
{
	// If we're going to display a dialog box, we need a human
	// view to interact with.

	HumanView* pView = GetHumanView();

	if (!pView)
	{
		// No Human View attached.
		return defaultAnswer;
	}

	if (m_HasModalDialog & 0x10000000)
	{
		//GCC_ASSERT(0 & "Too many nested dialogs!");
		return defaultAnswer;
	}

	//GCC_ASSERT(GetHwnd() != NULL && _T("Main Window is NULL!"));
	if ((GetHwnd() != NULL) && IsIconic(GetHwnd()))
	{
		FlashWhileMinimized();
	}

	m_HasModalDialog <<= 1;
	m_HasModalDialog |= 1;

	//pView->VPushElement(pModalScreen);

	LPARAM lParam = 0;
	int result = PumpUntilMessage(g_MsgEndModal, NULL, &lParam);

	if (lParam != 0)
	{
		if (lParam == g_QuitNoPrompt)
			result = defaultAnswer;
		else
			result = (int)lParam;
	}

	// Remove pModalScreen from pView
	m_HasModalDialog >>= 1;

	return result;
}

// EngineApp::PumpUntilMessage
int EngineApp::PumpUntilMessage(UINT msgEnd, WPARAM *pWParam, LPARAM *pLParam)
{
	int currentTime = timeGetTime();
	MSG msg;
	for (;;)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (msg.message == WM_CLOSE)
			{
				m_bQuitting = true;
				GetMessage(&msg, NULL, 0, 0);
				break;
			}
			else
			{
				// Default processing
				if (GetMessage(&msg, NULL, NULL, NULL))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}

				// Are we done?
				if (msg.message == msgEnd)
					break;
			}
		}
		else
		{
			// Update the game views, but nothing else!
			// Remember this is a modal screen.
			if (m_pGame)
			{
				int timeNow = timeGetTime();
				int deltaMilliseconds = timeNow - currentTime;
				for (GameViewList::iterator i = m_pGame->m_gameViews.begin(); i != m_pGame->m_gameViews.end(); ++i)
				{
					(*i)->VOnUpdate(deltaMilliseconds);
				}
				currentTime = timeNow;
				// Render Environment
			}
		}
	}
	if (pLParam)
		*pLParam = msg.lParam;
	if (pWParam)
		*pWParam = msg.wParam;

	return 0;
}

// This function removes all of a *SPECIFIC* type of message from the queue
int EngineApp::EatSpecificMessages(UINT msgType, optional<LPARAM> lParam, optional<WPARAM> wParam)
{
	bool done = false;

	while (!done)
	{
		MSG msg;

		if (PeekMessage(&msg, NULL, msgType, msgType, PM_NOREMOVE))
		{
			bool valid = true;

			if (lParam.valid())
			{
				valid &= (*lParam == msg.lParam);
			}

			if (wParam.valid())
			{
				valid &= (*wParam == msg.wParam);
			}

			if (valid)
			{
				// Soak!
				GetMessage(&msg, NULL, msgType, msgType);
			}
			else
			{
				done = true;
			}
		}
		else
		{
			done = true;	// No more messages!
		}
	}

	return 0;
}

// Rendering calls

//--------------------------------------------------------------------------------------
// This callback function will be called once at the beginning of every frame. This is the
// best location for your application to handle updates to the scene, but is not 
// intended to contain actual rendering calls, which should instead be placed in the 
// OnFrameRender callback.  
//--------------------------------------------------------------------------------------
void CALLBACK EngineApp::OnUpdateGame(double fTime, float fElapsedTime, void *pUserContext)
{
	if (g_pApp->HasModalDialog())
	{
		// don't update the game if a modal dialog is up.
		return;
	}

	if (g_pApp->m_bQuitting)
	{
		PostMessage(g_pApp->GetHwnd(), WM_CLOSE, 0, 0);
	}

	if (g_pApp->m_pGame)
	{
		// Event Manager

		// Socket Manager

		g_pApp->m_pGame->VOnUpdate(float(fTime), fElapsedTime);
	}
}