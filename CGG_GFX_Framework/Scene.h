#pragma once
#ifndef _SCECE_H_
#define _SCENE_H_

#include <memory>
#include <vector>

#include "Object.h"
#include "Tracer.h"

class Scene
{
public:
	Scene();
	~Scene();

	void Init(int _windowWidth, int _windowHeight);

	void Render();

private:
	std::vector<std::shared_ptr<Object>> m_objects;
	int m_windowW, m_windowH;
	std::shared_ptr<Tracer> m_tracer;
};

#endif // !_SCECE_H_



