
#include <cmath>
#include "CGG_Main.h"
#include "Ray.h"
#include "Camera.h"
#include "Tracer.h"

void clamp_colour(glm::vec3& _colour);

int main(int argc, char *argv[])
{
	// Variables for storing window dimensions
	int windowWidth = 900;
	int windowHeight = 900;

	// Call CGG::Init to initialise and create your window
	// Tell it what size you want the window to be
	if( !CGG::Init( windowWidth, windowHeight ) )
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}

	Camera cam;
	sphere sphere1(450, 700, 100 ,100 );
	sphere sphere2(450, 100, 100, 50);

	// Sets every pixel to the same _colour
	// parameters are RGBA, numbers are from 0 to 255
	CGG::SetBackground( 0,0,0 );

	float t;
	glm::vec3 red = glm::vec3(255.0f, 0.0f, 0.0f);
	glm::vec3 white = glm::vec3(255.0f);

	for (int x = 0; x < windowWidth; x++)
	{
		for (int y = 0; y < windowHeight; y++)
		{
			glm::vec2 coord(x, y);
			Ray currentRay = cam.createRay(coord);
			

			if (sphere1.interception(currentRay,t))
			{
				glm::vec3 pi = currentRay.origin + currentRay.direction * t;
				glm::vec3 L = glm::vec3(450.0f, 450.0f, 0.0f) - pi;
				glm::vec3 N = sphere1.GetNormal(pi);
				float dt = glm::dot(glm::normalize(L), glm::normalize(N));

				glm::vec3 colour = (red + white * dt) * 0.5f;
				clamp_colour(colour);
				CGG::DrawPixel(x, y, colour.x, colour.y, colour.z);
			}

			if (sphere2.interception(currentRay, t))
			{
				glm::vec3 pi = currentRay.origin + currentRay.direction * t;
				glm::vec3 L = glm::vec3(450.0f, 450.0f, 0.0f) - pi;
				glm::vec3 N = sphere2.GetNormal(pi);
				float dt = glm::dot(glm::normalize(L), glm::normalize(N));

				glm::vec3 colour = (red + white * dt) * 0.5f;
				clamp_colour(colour);
				CGG::DrawPixel(x, y, colour.x, colour.y, colour.z);
			}
		}
	}

	return CGG::ShowAndHold();
}

void clamp_colour(glm::vec3& _col)
{
	_col.x = (_col.x > 255) ? 255 : (_col.x < 0) ? 0 : _col.x;
	_col.y = (_col.y > 255) ? 255 : (_col.y < 0) ? 0 : _col.y;
	_col.z = (_col.z > 255) ? 255 : (_col.z < 0) ? 0 : _col.z;
}