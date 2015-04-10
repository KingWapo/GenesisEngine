#pragma once

#include "ActorComponent.h"

enum KeyCode {
	SPACE = 0x20,
	LEFT = 0x25,
	UP = 0x26,
	RIGHT = 0x27,
	DOWN = 0x28,
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

enum ControllerButton {
	A_BTN = 0x00,
	B_BTN = 0x01,
	X_BTN = 0x02,
	Y_BTN = 0x03,
	LB = 0x04,
	LT = 0x05,
	RB = 0x06,
	RT = 0x07,
	L_STICK = 0x08,
	R_STICK = 0x09,
	START = 0x0A,
	BACK = 0x0B
};


enum AxisSource {
	WASD,
	ARROWS,
	LEFT_STICK,
	RIGHT_STICK
};

class InputManager : public ActorComponent {
public:
	virtual bool onKeyDown(unsigned int keyID) = 0;
	virtual bool onKeyUp(unsigned int keyId) = 0;
	virtual bool isKeyPressed(unsigned int keyID) = 0;
	virtual float horizontalAxis(AxisSource axisSource) = 0;
	virtual float verticalAxis(AxisSource axisSource) = 0;
};