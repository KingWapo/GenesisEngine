#include "InputManager.h"
#include <Windows.h>
#include <iostream>

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

bool InputManager::onKeyDown(unsigned int keyID) {
	updateKeyState(keyID);

	if ((_keyMap[keyID] & 0x11) == _keyOnDown) {
		std::cout << (int) _keyMap[keyID] << ": key down" << std::endl;
		return true;
	}

	return false;
}

bool InputManager::onKeyUp(unsigned int keyID) {
	updateKeyState(keyID);

	if ((_keyMap[keyID] & 0x11) == _keyOnUp) {
		std::cout << (int) _keyMap[keyID] << ": key up" << std::endl;

		return true;
	}

	return false;
}

bool InputManager::isKeyPressed(unsigned int keyID) {
	updateKeyState(keyID);

	if ((_keyMap[keyID] & 0x11) == _keyDown) {
		std::cout << (int) _keyMap[keyID] << ": key held" << std::endl;

		return true;
	}

	return false;
}

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