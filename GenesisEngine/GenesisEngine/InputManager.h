#pragma once

#include <unordered_map>
#include <glm\glm.hpp>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void setMouseCoords(float x, float y);

	// key calls
	static bool onKeyDown(unsigned int keyID);
	static bool onKeyUp(unsigned int keyID);
	static bool isKeyPressed(unsigned int keyID);

	//getters
	glm::vec2 getMouseCoords() const { return _mouseCoords; }

private:
	// maintain state of key events
	static void updateKeyState(unsigned int keyID);

	// map stores char in this format, 0xAB
	// A represents state during this call, 1 down, 0 up
	// B represents state during last call, 1 down, 0 up
	static std::unordered_map<unsigned int, unsigned char> _keyMap;
	glm::vec2 _mouseCoords;

	// key is down now and was last update
	static const unsigned char _keyDown = 0x11;
	// key is up now and was last update
	static const unsigned char _keyUp = 0x00;
	// key is down now but wasn't last update
	static const unsigned char _keyOnDown = 0x10;
	// key is up now but wasn't last update
	static const unsigned char _keyOnUp = 0x01;
};