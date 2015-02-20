#include "CustomScript.h"
#include "Actor.h"

#include <memory>
#include <iostream>
#include <Windows.h>

const char* CustomScript::g_Name = "CustomScript";

CustomScript::CustomScript()
{
}


CustomScript::~CustomScript()
{
}

bool CustomScript::vInit() {
	GCC_ASSERT(m_pOwner.get() != NULL);

	Actor* l_owner = static_cast<Actor*>(m_pOwner.get());

	m_input = l_owner->GetComponent<InputManager>("InputManager").lock();
	m_transform = l_owner->GetComponent<Transform2dComponent>("Transform2dComponent").lock();

	return true;
}

bool CustomScript::vUpdate(int deltaMs) {
	GCC_ASSERT(m_input.get() != NULL);
	GCC_ASSERT(m_transform.get() != NULL);

	if (m_input->onKeyDown(VK_SPACE)) {
		std::cout << "Space pressed" << std::endl;
		std::cout << m_transform->GetLocation().toString() << std::endl;
	}

	if (m_input->onKeyUp(VK_SPACE)) {
		std::cout << "Space released" << std::endl;
	}

	return true;
}
