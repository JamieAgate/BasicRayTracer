#pragma once
#ifndef _SCECE_H_
#define _SCENE_H_

#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <gtc/matrix_transform.hpp>

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
	void RenderSection(int _minx, int _maxX, int _minY, int _maxY);
	
	std::mutex m_mutex;
	std::vector<std::thread> m_threads;

	glm::mat4 m_cameraToWorld;
	

	std::vector<glm::vec3> m_imageV;
	std::vector<std::shared_ptr<Object>> m_objects;
	std::shared_ptr<Tracer> m_tracer;
	int m_windowW, m_windowH;
};

#endif // !_SCECE_H_



