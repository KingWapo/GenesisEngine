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
		vector<StrongActorComponentPtr>::iterator iter;
		for (iter = m_renderableComponents.begin(); iter != m_renderableComponents.end(); ++iter)
		{
			(*iter)->vDraw();
		}
	}
}

void Scene::addRenderableComponent(StrongActorComponentPtr p_comp)
{
	m_renderableComponents.push_back(p_comp);
}