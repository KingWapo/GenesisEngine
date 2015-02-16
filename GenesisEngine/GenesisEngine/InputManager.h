#pragma once

#include "ActorComponent.h"

#include <unordered_map>
#include <glm\glm.hpp>

class InputManager : public ActorComponent
{
public:
	InputManager();
	~InputManager();

	void setMouseCoords(float x, float y);

	// called first each update
	void preUpdate();

	// key calls
	bool onKeyDown(unsigned int keyID);
	bool onKeyUp(unsigned int keyID);
	bool isKeyPressed(unsigned int keyID);

	//getters
	glm::vec2 getMouseCoords() const { return _mouseCoords; }

	// component overrides
	static const char* g_Name;
	virtual const char* VGetName() const { return g_Name; }

	virtual bool VInit(TiXmlElement* pData) override;
	virtual TiXmlElement* VGenerateXml(void) override;

	virtual void VUpdate(int deltaMs);

private:
	// maintain state of key events
	void updateKeyState(unsigned int keyID);

	// map stores char in this format, 0xAB
	// A represents state during this call, 1 down, 0 up
	// B represents state during last call, 1 down, 0 up
	std::unordered_map<unsigned int, unsigned char> _keyMap;
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