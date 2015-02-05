#pragma once

#include <Windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <mmsystem.h>

#include <algorithm>
#include <list>
#include <vector>
#include <queue>
#include <map>

// Engine Files Included
//#include <Windows.h>
//#include "Types.h"

// Inlcudes <string>
#include "Logger.h"

// #include <memory>
#include "Templates.h"

const int MEGABYTE = 1024 * 1024;
const float SIXTY_HERTZ = 16.66f;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

using std::tr1::shared_ptr;
using std::tr1::weak_ptr;
using std::tr1::static_pointer_cast;
using std::tr1::dynamic_pointer_cast;

class GCC_noncopyable
{
private:
	GCC_noncopyable(const GCC_noncopyable& x);
	GCC_noncopyable& operator=(const GCC_noncopyable& x);
public:
	GCC_noncopyable() {}; // Default constructor  
};


struct AppMsg
{
	HWND m_hWnd;
	UINT m_uMsg;
	WPARAM m_wParam;
	LPARAM m_lParam;
};

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

#if !defined(SAFE_DELETE)
#define SAFE_DELETE(x) if(x) delete x; x=NULL;
#endif

#if !defined(SAFE_DELETE_ARRAY)
#define SAFE_DELETE_ARRAY(x) if (x) delete [] x; x=NULL; 
#endif

#if !defined(SAFE_RELEASE)
#define SAFE_RELEASE(x) if(x) x->Release(); x=NULL;
#endif

#ifdef UNICODE
#define _tcssprintf wsprintf
#define tcsplitpath _wsplitpath
#else
#define _tcssprintf sprintf
#define tcsplitpath _splitpath
#endif

#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)") : Warning Msg: "

extern int GenesisEntry(int argc, char *argv[]);