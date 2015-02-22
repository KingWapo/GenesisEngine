#pragma once

#include "ActorComponent.h"

#include <unordered_map>

enum KeyCode {
	LEFT  = 0x25,
	UP    = 0x26,
	RIGHT = 0x27,
	DOWN  = 0x28,
	A = 0x41,
	D = 0x44,
	S = 0x53,
	W = 0x57
};

class InputManager : public ActorComponent
{
public:
	InputManager();
	~InputManager();

	// called first each update
	bool preUpdate();

	// key calls
	bool onKeyDown(unsigned int keyID);
	bool onKeyUp(unsigned int keyID);
	bool isKeyPressed(unsigned int keyID);
	int horizontalAxis();
	int verticalAxis();

	// component overrides
	static const char* g_Name;
	virtual const char* VGetName() const { return g_Name; }

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