#include "InputManager.h"
#include <Windows.h>
#include <iostream>

const char* InputManager::g_Name = "InputManager";

InputManager::InputManager() : _mouseCoords(0.0f)
{
}


InputManager::~InputManager()
{
}

void InputManager::setMouseCoords(float x, float y) {
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}

/** CALL EACH UPDATE BEFORE CHECKING KEY STATE **/
/** ITERATE OVER MAP AND UPDATE ALL EXISTING PAIRS **/
void InputManager::preUpdate() {
	std::unordered_map<unsigned int, unsigned char>::iterator iter;
	for (iter = _keyMap.begin(); iter != _keyMap.end(); ++iter) {
		unsigned int key = iter->first;

		updateKeyState(key);
	}
}

/** RETURN TRUE IF KEY WAS JUST PRESSED **/
bool InputManager::onKeyDown(unsigned int keyID) {
	return ((_keyMap[keyID] & 0x11) == _keyOnDown);
}

/** RETURN TRUE IF KEY WAS JUST RELEASED **/
bool InputManager::onKeyUp(unsigned int keyID) {
	return ((_keyMap[keyID] & 0x11) == _keyOnUp);
}

/** RETURN TRUE IF KEY IS HELD **/
bool InputManager::isKeyPressed(unsigned int keyID) {
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
bool InputManager::VInit(TiXmlElement* pData) {
	return true;
}

TiXmlElement* InputManager::VGenerateXml() {
	return NULL;
}

void InputManager::VUpdate(int deltaMs) {
	preUpdate();

	if (onKeyDown(VK_LSHIFT)) {
		std::cout << (int)_keyMap[VK_LSHIFT] << ": key down" << std::endl;
	}

	if (onKeyUp(VK_LSHIFT)) {
		std::cout << (int)_keyMap[VK_LSHIFT] << ": key up" << std::endl;
	}

	if (isKeyPressed(VK_LSHIFT)) {
		std::cout << (int)_keyMap[VK_LSHIFT] << ": key held" << std::endl;
	}
}