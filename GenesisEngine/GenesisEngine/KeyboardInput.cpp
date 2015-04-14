#include "KeyboardInput.h"
#include <Windows.h>
#include <iostream>
#include <utility>

KeyboardInput::KeyboardInput()
{
}


KeyboardInput::~KeyboardInput()
{
}

/** CALL EACH UPDATE BEFORE CHECKING KEY STATE **/
/** ITERATE OVER MAP AND UPDATE ALL EXISTING PAIRS **/
bool KeyboardInput::preUpdate() {
	std::unordered_map<unsigned int, unsigned char>::iterator iter;
	for (iter = m_keyMap.begin(); iter != m_keyMap.end(); ++iter) {
		unsigned int key = iter->first;

		updateKeyState(key);
	}

	// add check that key was updated
	return true;
}

/** IF KEY IS NOT IN MAP, ADD IT **/
void KeyboardInput::checkNewKey(unsigned int keyID) {
	if (m_keyMap.count(keyID) == 0) {
		std::pair<unsigned int, unsigned char> key = std::make_pair(keyID, 0);
		m_keyMap.insert(key);
	}
}

/** RETURN -1 IF MOVING LEFT, 1 IF MOVING RIGHT, 0 IF NOT MOVING **/
float KeyboardInput::horizontalAxis(AxisSource axisSource) {
	bool left;
	bool right;

	switch (axisSource) {
	case AxisSource::LEFT_AXIS:
		left = isKeyPressed(KeyCode::A);
		right = isKeyPressed(KeyCode::D);
		break;

	case AxisSource::RIGHT_AXIS:
		left = isKeyPressed(KeyCode::LEFT);
		right = isKeyPressed(KeyCode::RIGHT);
		break;

	default:
		left = false;
		right = false;
		break;
	}

	if (left && !right) {
		return -1.0f;
	}

	if (right && !left) {
		return 1.0f;
	}

	return 0.0f;
}

/** RETURN 1 IF MOVING UP, -1 IF MOVING DOWN, 0 IF NOT MOVING **/
float KeyboardInput::verticalAxis(AxisSource axisSource) {
	bool up;
	bool down;

	switch (axisSource) {
	case AxisSource::LEFT_AXIS:
		up = isKeyPressed(KeyCode::W);
		down = isKeyPressed(KeyCode::S);
		break;

	case AxisSource::RIGHT_AXIS:
		up = isKeyPressed(KeyCode::UP);
		down = isKeyPressed(KeyCode::DOWN);
		break;

	default:
		up = false;
		down = false;
		break;
	}

	if (up && !down) {
		return 1.0f;
	}

	if (down && !up) {
		return -1.0f;
	}

	return 0.0f;
}

/** RETURN TRUE IF KEY WAS JUST PRESSED **/
bool KeyboardInput::onKeyDown(unsigned int keyID) {
	checkNewKey(keyID);

	return ((m_keyMap[keyID] & 0x11) == m_keyOnDown);
}

/** RETURN TRUE IF KEY WAS JUST RELEASED **/
bool KeyboardInput::onKeyUp(unsigned int keyID) {
	checkNewKey(keyID);

	return ((m_keyMap[keyID] & 0x11) == m_keyOnUp);
}

/** RETURN TRUE IF KEY IS HELD **/
bool KeyboardInput::isKeyPressed(unsigned int keyID) {
	checkNewKey(keyID);

	return ((m_keyMap[keyID] & 0x11) == m_keyDown);
}

/** UPDATE STATE OF KEY SPECIFIED IN PARAMETER **/
void KeyboardInput::updateKeyState(unsigned int keyID) {
	if (m_keyMap[keyID] == m_keyOnDown) {
		// if key was pressed last update
		// update right bit

		// key is in held state
		m_keyMap[keyID] = m_keyDown;
	}
	else if (m_keyMap[keyID] == m_keyOnUp) {
		// if key was released last update
		// update right bit

		// key is in released state
		m_keyMap[keyID] = m_keyUp;
	}

	bool keyStateDown = (GetAsyncKeyState(keyID) & 0x8000) == 0x8000;
	if (keyStateDown && m_keyMap[keyID] == m_keyUp) {
		// if key was just pressed
		// update left bit

		// key is in on key down state
		m_keyMap[keyID] = m_keyOnDown;
	}
	else if (!keyStateDown && m_keyMap[keyID] == m_keyDown) {
		// if key was just released
		// update left bit

		// key is in on key up state
		m_keyMap[keyID] = m_keyOnUp;
	}
}

/** ACTOR COMPONENT OVERRIDES **/
bool KeyboardInput::vInit() {
	return true;
}

bool KeyboardInput::vUpdate(int deltaMs) {
	return preUpdate();
}