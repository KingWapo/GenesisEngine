#pragma once

#include "ActorComponent.h"
#include "InputManager.h"

class CustomScript : public ActorComponent
{
public:
	CustomScript();
	~CustomScript();

	static const char* g_Name;
	virtual const char* VGetName() const { return g_Name; }

	virtual bool vInit(void) override;
	virtual bool vUpdate(int deltaMs) override;

private:
	shared_ptr<InputManager> m_input;
};

