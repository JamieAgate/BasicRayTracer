#include "Scene.h"
#include "CGG_Main.h"
#include "Sphere.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Init(int _windowWidth, int _windowHeight)
{
	m_windowW = _windowWidth;
	m_windowH = _windowHeight;

	m_tracer = std::make_shared<Tracer>();

	m_objects.push_back(std::make_shared<Sphere>(450, 700, 100, 100));
	m_objects.push_back(std::make_shared<Sphere>(450, 100, 100, 50));
}

void Scene::Render()
{
	for (size_t x = 0; x < m_windowW; x++)
	{
		for (size_t y = 0; y < m_windowH; y++)
		{
			glm::vec4 colour = m_tracer->TraceRay(x, y, m_objects);
			CGG::DrawPixel(x, y, colour.x, colour.y, colour.z);

		}
		CGG::Present();
	}
}
