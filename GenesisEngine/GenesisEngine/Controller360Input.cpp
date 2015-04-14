#include "Controller360Input.h"

Controller360Input::Controller360Input()
{
}


Controller360Input::~Controller360Input()
{
}

bool Controller360Input::vInit() {
	m_keyMap.insert(std::make_pair(ControllerButton::A_BTN, 0));
	m_keyMap.insert(std::make_pair(ControllerButton::B_BTN, 0));
	m_keyMap.insert(std::make_pair(ControllerButton::X_BTN, 0));
	m_keyMap.insert(std::make_pair(ControllerButton::Y_BTN, 0));
	m_keyMap.insert(std::make_pair(ControllerButton::UP_DPD, 0));
	m_keyMap.insert(std::make_pair(ControllerButton::DOWN_DPD, 0));
	m_keyMap.insert(std::make_pair(ControllerButton::LEFT_DPD, 0));
	m_keyMap.insert(std::make_pair(ControllerButton::RIGHT_DPD, 0));
	m_keyMap.insert(std::make_pair(ControllerButton::LB, 0));
	m_keyMap.insert(std::make_pair(ControllerButton::RB, 0));
	m_keyMap.insert(std::make_pair(ControllerButton::START, 0));
	m_keyMap.insert(std::make_pair(ControllerButton::BACK, 0));
	m_keyMap.insert(std::make_pair(ControllerButton::L_STICK, 0));
	m_keyMap.insert(std::make_pair(ControllerButton::R_STICK, 0));
	return findController();
}

bool Controller360Input::vUpdate(int deltaMs) {
	lastCheckMS += deltaMs;

	if (portID != INVALID_PORT) {
		DWORD dwResult = 0;

		ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

		dwResult = XInputGetState(portID, &controllerState);

		if (dwResult == ERROR_SUCCESS) {
			return preUpdate();
		}
		else {
			return findController();
		}
	}
	else {
		 return findController();
	}

	return true;
}

bool Controller360Input::findController() {
	if (lastCheckMS >= checkDelayMS) {
		DWORD dwResult = 0;

		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
			XINPUT_STATE state;

			ZeroMemory(&state, sizeof(XINPUT_STATE));

			dwResult = XInputGetState(i, &state);

			if (dwResult == ERROR_SUCCESS) {
				// controller is connected
				// set id of controller used in this instance
				portID = i;
				return true;
			}
		}

		portID = INVALID_PORT;
		return false;
	}

	return false;
}

bool Controller360Input::onKeyDown(unsigned int keyID) {
	return ((m_keyMap[keyID] & 0x11) == m_keyOnDown);
}

bool Controller360Input::onKeyUp(unsigned int keyID) {
	return ((m_keyMap[keyID] & 0x11) == m_keyOnUp);
}

bool Controller360Input::isKeyPressed(unsigned int keyID) {
	return ((m_keyMap[keyID] & 0x11) == m_keyDown);
}

float Controller360Input::horizontalAxis(AxisSource axisSource) {
	float axis = 0;
	float axisX;
	float axisY;

	switch (axisSource) {
	case AxisSource::LEFT_AXIS:
		axisX = controllerState.Gamepad.sThumbLX;
		axisY = controllerState.Gamepad.sThumbLY;
		axis = adjDeadZone(axisX, axisY, true);
		break;
	case AxisSource::RIGHT_AXIS:
		axisX = controllerState.Gamepad.sThumbRX;
		axisY = controllerState.Gamepad.sThumbRY;
		axis = adjDeadZone(axisX, axisY, true);
		break;
	case AxisSource::TRIGGER:
		float rTrig = controllerState.Gamepad.bRightTrigger;
		float lTrig = controllerState.Gamepad.bLeftTrigger;
		axis = (rTrig - lTrig) / 255.0f;
		break;
	}
	return axis;
}

float Controller360Input::verticalAxis(AxisSource axisSource) {
	float axis;
	float axisX;
	float axisY;

	switch (axisSource) {
	case AxisSource::LEFT_AXIS:
		axisX = controllerState.Gamepad.sThumbLX;
		axisY = controllerState.Gamepad.sThumbLY;
		axis = adjDeadZone(axisX, axisY, false);
		break;
	case AxisSource::RIGHT_AXIS:
		axisX = controllerState.Gamepad.sThumbRX;
		axisY = controllerState.Gamepad.sThumbRY;
		axis = adjDeadZone(axisX, axisY, false);
		break;
	}
	return axis;
}

float Controller360Input::adjDeadZone(float axisX, float axisY, bool useX) {
	// how far is it pushed
	float mag = sqrt(axisX * axisX + axisY * axisY);

	// determine direction
	float normX = axisX / mag;
	float normY = axisY / mag;

	float normMag = 0;

	// check if in circular dead zone
	if (mag > deadzone) {
		// clip magnitude at expected max
		if (mag > 32767) mag = 32767;

		// adjust to end of dead zone
		mag -= deadzone;

		// normalize magnitude
		normMag = mag / (32767 - deadzone);
	}
	// zero out magnitude
	else {
		mag = 0.0f;
		normMag = 0.0f;
		normX = 0.0f;
		normY = 0.0f;
	}

	if (useX) {
		return normX;
	}
	else {
		return normY;
	}
}

void Controller360Input::updateKeyState(unsigned int keyID) {
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
	bool keyStateDown = (keyID & controllerState.Gamepad.wButtons) != 0;
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

bool Controller360Input::preUpdate() {
	std::unordered_map<unsigned int, unsigned char>::iterator iter;
	for (iter = m_keyMap.begin(); iter != m_keyMap.end(); ++iter) {
		unsigned int key = iter->first;

		updateKeyState(key);
	}

	// add check that key was updated
	return true;
}