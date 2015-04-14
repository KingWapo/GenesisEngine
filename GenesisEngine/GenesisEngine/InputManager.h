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
	A_BTN = 0x1000,
	B_BTN = 0x2000,
	X_BTN = 0x4000,
	Y_BTN = 0x8000,
	UP_DPD    = 0x0001,
	DOWN_DPD  = 0x0002,
	LEFT_DPD  = 0x0004,
	RIGHT_DPD = 0x0008,
	LB = 0x0100,
	RB = 0x0200,
	START   = 0x0010,
	BACK    = 0x0020,
	L_STICK = 0x0040,
	R_STICK = 0x0080
};


// left (wasd, left stick), right (arrows, right stick), trigger (controller)
enum AxisSource {
	LEFT_AXIS, RIGHT_AXIS, TRIGGER
};

class InputManager : public ActorComponent {
public:
	virtual bool onKeyDown(unsigned int keyID) = 0;
	virtual bool onKeyUp(unsigned int keyId) = 0;
	virtual bool isKeyPressed(unsigned int keyID) = 0;
	virtual float horizontalAxis(AxisSource axisSource) = 0;
	virtual float verticalAxis(AxisSource axisSource) = 0;

	static const char *g_name;
	virtual const char *VGetName() const { return g_name; }
};