#pragma once

#include "ActorComponent.h"

#include <unordered_map>

enum KeyCode {
	LEFT  = 0x25,
	UP    = 0x26,
	RIGHT = 0x27,
	DOWN  = 0x28,
	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A
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