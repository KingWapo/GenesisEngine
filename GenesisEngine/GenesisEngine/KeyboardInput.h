#pragma once

#include "InputManager.h"

#include <unordered_map>

class KeyboardInput : public InputManager
{
public:
	KeyboardInput();
	~KeyboardInput();

	// called first each update
	bool preUpdate();

	// key calls
	virtual bool onKeyDown(unsigned int keyID) override;
	virtual bool onKeyUp(unsigned int keyID) override;
	virtual bool isKeyPressed(unsigned int keyID) override;
	virtual float horizontalAxis(AxisSource axisSource) override;
	virtual float verticalAxis(AxisSource axisSource) override;

	virtual bool vInit(void) override;
	virtual bool vUpdate(int deltaMs) override;

private:
	// maintain state of key events
	void updateKeyState(unsigned int keyID);

	void checkNewKey(unsigned int keyID);

	// map stores char in this format, 0xAB
	// A represents state during this call, 1 down, 0 up
	// B represents state during last call, 1 down, 0 up
	std::unordered_map<unsigned int, unsigned char> m_keyMap;

	// key is down now and was last update
	static const unsigned char m_keyDown = 0x11;
	// key is up now and was last update
	static const unsigned char m_keyUp = 0x00;
	// key is down now but wasn't last update
	static const unsigned char m_keyOnDown = 0x10;
	// key is up now but wasn't last update
	static const unsigned char m_keyOnUp = 0x01;
};