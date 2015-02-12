#include "TestGame.h"
#include "TestGameView.h"
#include "InputManager.h"
#include <iostream>

using namespace std;

std::unordered_map<unsigned int, unsigned char> InputManager::_keyMap;
TestGameApp *g_TestGameApp;

// Main? Call the Engine Code main
int main(int argc, char *argv[])
{
	//while (!InputManager::onKeyDown(VK_SPACE)) {
		//InputManager::onKeyDown(VK_LSHIFT);
		//InputManager::onKeyUp(VK_LSHIFT);
		//InputManager::isKeyPressed(VK_LSHIFT);
	//}

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