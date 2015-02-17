#include "Scene.h"

using namespace std;

Scene::Scene()
{
}


Scene::~Scene()
{
	while (!m_renderableComponents.empty())
	{
		//(m_renderableComponents.back()).Destroy();
		m_renderableComponents.pop_back();
	}
}

void Scene::draw()
{
	bool somethingClever = false;
	if (somethingClever)
	{
		for (vector<StrongActorComponentPtr>::iterator it = m_renderableComponents.begin(); it != m_renderableComponents.end(); ++it)
		{
			(*it)->vDraw();
		}
	}
}

void Scene::addRenderableComponent(StrongActorComponentPtr p_comp)
{
	m_renderableComponents.push_back(p_comp);
}