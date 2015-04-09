#include "Controller360Input.h"

const char* Controller360Input::g_Name = "Controller360Input";

Controller360Input::Controller360Input()
{
}


Controller360Input::~Controller360Input()
{
}

bool Controller360Input::vInit() {
	return findController();
}

bool Controller360Input::vUpdate(int deltaMs) {
	lastCheckMS += deltaMs;

	if (portID != INVALID_PORT) {
		DWORD dwResult = 0;

		ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

		//dwResult = XInputGetState(portID, &controllerState);

		if (dwResult == ERROR_SUCCESS) {
			// controller is valid
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

			//dwResult = XInputGetState(i, &state);

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
	return false;
}

bool Controller360Input::onKeyUp(unsigned int keyID) {
	return false;
}

bool Controller360Input::isKeyPressed(unsigned int keyID) {
	return false;
}

float Controller360Input::horizontalAxis(AxisSource axisSource) {
	return 0;
}

float Controller360Input::verticalAxis(AxisSource axisSource) {
	return 0;
}