#pragma once

#include "UserInterface.h"
#include "HumanView.h"

class TestView : public HumanView
{
protected:
	bool m_bShowUI;
	std::wstring m_gameplayText;

public:
	TestView();
	TestView(shared_ptr<IRenderer> renderer);
	virtual ~TestView();
	
	virtual LRESULT CALLBACK VOnMsgProc(AppMsg msg);
	virtual void VOnUpdate(unsigned long deltaMs);
	virtual void VOnAttach(GameViewId vid, ActorId aid);

	virtual bool VLoadGameDelegate();
};