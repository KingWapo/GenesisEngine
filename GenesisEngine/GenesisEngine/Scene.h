#pragma once
#include <vector>
#include "SDLRenderableComponent.h"

using namespace std;

class Scene
{
private:
	vector<StrongActorComponentPtr> m_renderableComponents;

public:
	Scene();
	~Scene();

	void draw();

	void addRenderableComponent(StrongActorComponentPtr p_comp);
};

