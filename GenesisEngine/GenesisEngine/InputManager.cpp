#include "InputManager.h"
#include <Windows.h>
#include <iostream>
#include <utility>

const char* InputManager::g_Name = "InputManager";

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

/** CALL EACH UPDATE BEFORE CHECKING KEY STATE **/
/** ITERATE OVER MAP AND UPDATE ALL EXISTING PAIRS **/
bool InputManager::preUpdate() {
	std::unordered_map<unsigned int, unsigned char>::iterator iter;
	for (iter = _keyMap.begin(); iter != _keyMap.end(); ++iter) {
		unsigned int key = iter->first;

		updateKeyState(key);
	}

	// add check that key was updated
	return true;
}

/** IF KEY IS NOT IN MAP, ADD IT **/
void InputManager::checkNewKey(unsigned int keyID) {
	if (_keyMap.count(keyID) == 0) {
		std::pair<unsigned int, unsigned char> key = std::make_pair(keyID, 0);
		_keyMap.insert(key);
	}
}

/** RETURN TRUE IF KEY WAS JUST PRESSED **/
bool InputManager::onKeyDown(unsigned int keyID) {
	checkNewKey(keyID);

	return ((_keyMap[keyID] & 0x11) == _keyOnDown);
}

/** RETURN TRUE IF KEY WAS JUST RELEASED **/
bool InputManager::onKeyUp(unsigned int keyID) {
	checkNewKey(keyID);

	return ((_keyMap[keyID] & 0x11) == _keyOnUp);
}

/** RETURN TRUE IF KEY IS HELD **/
bool InputManager::isKeyPressed(unsigned int keyID) {
	checkNewKey(keyID);

	return ((_keyMap[keyID] & 0x11) == _keyDown);
}

/** UPDATE STATE OF KEY SPECIFIED IN PARAMETER **/
void InputManager::updateKeyState(unsigned int keyID) {
	if (_keyMap[keyID] == _keyOnDown) {
		// if key was pressed last update
		// update right bit

		// key is in held state
		_keyMap[keyID] = _keyDown;
	}
	else if (_keyMap[keyID] == _keyOnUp) {
		// if key was released last update
		// update right bit

		// key is in released state
		_keyMap[keyID] = _keyUp;
	}

	bool keyStateDown = (GetAsyncKeyState(keyID) & 0x8000) == 0x8000;
	if (keyStateDown && _keyMap[keyID] == _keyUp) {
		// if key was just pressed
		// update left bit

		// key is in on key down state
		_keyMap[keyID] = _keyOnDown;
	}
	else if (!keyStateDown && _keyMap[keyID] == _keyDown) {
		// if key was just released
		// update left bit

		// key is in on key up state
		_keyMap[keyID] = _keyOnUp;
	}
}

/** ACTOR COMPONENT OVERRIDES **/
bool InputManager::vInit() {
	return true;
}

bool InputManager::vUpdate(int deltaMs) {
	return preUpdate();
}