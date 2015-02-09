#include "TestGame.h"
#include "TestGameView.h"
#include <iostream>

using namespace std;

TestGameApp *g_TestGameApp;

// Main? Call the Engine Code main
int main(int argc, char *argv[])
{
	cout << "At least I get in here....right?" << endl;
	cout.flush();

	GenesisEntry(argc, argv);

	return 0;
}

HICON TestGameApp::VGetIcon()
{
	return NULL;
}

void TestGameApp::VRegisterGameEvents(void)
{
	
}
void TestGameApp::VCreateNetworkEventForwarder(void)
{

}
void TestGameApp::VDestroyNetworkEventForwarder(void)
{

}

BaseGameLogic *TestGameApp::VCreateGameAndView()
{
	m_pGame = GCC_NEW TestGameLogic();
	m_pGame->Init();

	shared_ptr<IGameView> testView(GCC_NEW TestView(NULL));
	m_pGame->VAddView(testView);

	return m_pGame;
}
std::shared_ptr<IGamePhysics> TestGameLogic::VGetGamePhysics()
{
	return NULL;
}

TestGameLogic::TestGameLogic()
{
	// CreatePhysics and register delegates
}

TestGameLogic::~TestGameLogic()
{
	// Remove Delegates
	// Destroy network stuffs
}

void TestGameLogic::VSetProxy()
{
	BaseGameLogic::VSetProxy();
}

void TestGameLogic::VAddView(shared_ptr<IGameView> pView, ActorId actor)
{
	BaseGameLogic::VAddView(pView, actor);
}

bool TestGameLogic::VLoadGameDelegate()
{
	return true;
}