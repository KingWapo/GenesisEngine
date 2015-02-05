#include "TestGameView.h"


TestView::TestView(shared_ptr<IRenderer> renderer) : HumanView(renderer)
{
	m_bShowUI = true;
}

TestView::~TestView()
{

}

LRESULT CALLBACK TestView::VOnMsgProc(AppMsg msg)
{
	if (HumanView::VOnMsgProc(msg))
		return 1;

	return 0;
}

void TestView::VOnUpdate(unsigned long deltaMs)
{
	HumanView::VOnUpdate(deltaMs);
	//shared_ptr<EvtData_Update_Tick>
}

void TestView::VOnAttach(GameViewId vid, ActorId aid)
{
	HumanView::VOnAttach(vid, aid);
}

bool TestView::VLoadGameDelegate()
{
	//m_pScene->VOnRestore();
	return true;
}