#pragma once
#pragma comment(lib, "Xinput9_1_0.lib")

#include "InputManager.h"

#include <Xinput.h>
#include <unordered_map>

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

	virtual bool vInit(void) override;
	virtual bool vUpdate(int deltaMs) override;

	float deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

private:
	DWORD portID;
	static const DWORD INVALID_PORT = static_cast<DWORD>(999);

	XINPUT_STATE controllerState;
	long lastCheckMS; // Time since last check for controller
	long checkDelayMS = 2000L; // 2 seconds

	bool findController();
	void updateKeyState(unsigned int keyID);
	bool preUpdate();

	float adjDeadZone(float axisX, float axisY, bool useX);

	std::unordered_map<unsigned, unsigned char> m_keyMap;

	// key is down now and was last update
	static const unsigned char m_keyDown = 0x11;
	// key is up now and was last update
	static const unsigned char m_keyUp = 0x00;
	// key is down now but wasn't last update
	static const unsigned char m_keyOnDown = 0x10;
	// key is up now but wasn't last update
	static const unsigned char m_keyOnUp = 0x01;
};

