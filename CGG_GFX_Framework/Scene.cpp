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

	m_tracer->AddLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(255.0f), 0.01f);
	//m_tracer->AddLight(glm::vec3(450.0f, 450.0f, -50.0f), glm::vec3(255.0f),0.01f);

	m_objects.push_back(std::make_shared<Sphere>(450, 200, 300, 100));
	m_objects.push_back(std::make_shared<Sphere>(450, 500, 300, 100, glm::vec3(0.0f,50.0f,0.0f),0.3f));

	for (int x = 0; x < m_windowW; x++)
	{
		for (int y = 0; y < m_windowH; y++)
		{
			m_imageV.push_back(glm::vec4(0.0f));
		}
	}
}



void Scene::RenderSection(int _minX, int _maxX, int _minY, int _maxY)
{
	for (int x = _minX; x < _maxX; x++)
	{
		for (int y = _minY; y < _maxY; y++)
		{
			glm::vec4 colour = m_tracer->TraceRay(glm::vec3(x, y, 0.0f),glm::vec3(0.0f, 0.0f, 1.0f), m_objects, 0);
			m_mutex.lock();
				m_imageV.at(m_windowW * y + x) = colour;
			m_mutex.unlock();
		}
	}
}

void Scene::Render()
{
	for (int x = 0; x < m_windowW; x+=100)
	{
		for (int y = 0; y < m_windowH; y+=100)
		{
			m_threads.push_back(std::thread(&Scene::RenderSection,this ,x, x + 100, y, y + 100));
		}
	}

	for (std::thread& t : m_threads)
	{
		t.join();
	}

	for (size_t x = 0; x < m_windowW; x++)
	{
		for (size_t y = 0; y < m_windowH; y++)
		{
			CGG::DrawPixel(x, y, m_imageV.at(m_windowW * y + x).x, m_imageV.at(m_windowW * y + x).y, m_imageV.at(m_windowW * y + x).z);
		}
	}
}
