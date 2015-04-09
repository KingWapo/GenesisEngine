#pragma once
//#pragma comment(lib, "Xinput.lib")

#include "InputManager.h"

#include <Xinput.h>

class Controller360Input : public InputManager
{
public:
	Controller360Input();
	~Controller360Input();

	virtual bool onKeyDown(unsigned int keyID) override;
	virtual bool onKeyUp(unsigned int keyID) override;
	virtual bool isKeyPressed(unsigned int keyID) override;
	virtual float horizontalAxis(AxisSource axisSource) override;
	virtual float verticalAxis(AxisSource axisSource) override;

	virtual const char* VGetName() const { return g_Name; }

	virtual bool vInit(void) override;
	virtual bool vUpdate(int deltaMs) override;

private:
	static const char *g_Name;
	DWORD portID;
	static const DWORD INVALID_PORT = static_cast<DWORD>(999);

	XINPUT_STATE controllerState;
	long lastCheckMS; // Time since last check for controller
	long checkDelayMS = 2000L; // 2 seconds

	bool findController();
};

