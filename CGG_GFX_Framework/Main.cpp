
#include <cmath>
#include "CGG_Main.h"
#include "Ray.h"
#include "Camera.h"
#include "Tracer.h"


int main(int argc, char *argv[])
{
	// Variables for storing window dimensions
	int windowWidth = 300;
	int windowHeight = 300;

	// Call CGG::Init to initialise and create your window
	// Tell it what size you want the window to be
	if( !CGG::Init( windowWidth, windowHeight ) )
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}

	Camera cam;
	Tracer trac;
	sphere sphere(150, 150, 0,10000 );
	// Sets every pixel to the same colour
	// parameters are RGBA, numbers are from 0 to 255
	CGG::SetBackground( 0,0,0 );

	for (int x = 0; x < windowWidth; x++)
	{
		for (int y = 0; y < windowHeight; y++)
		{
			glm::vec2 coord(x, y);
			Ray currentRay = cam.createRay(coord);
			//glm::vec4 colour = trac.tracer(currentRay);
			if (sphere.interception(currentRay))
			{
				CGG::DrawPixel(x, y, sphere.colour.x, 0, 0);
			}
		}
	}

	// Do any other DrawPixel calls here
	// ...

	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
	return CGG::ShowAndHold();
	
	

	
	
	// Advanced access - comment out the above DrawPixel and CGG::ShowAndHold lines, then uncomment the following:

	/*
	// Variable to keep track of time
	float timer = 0.0f;

	// This is our game loop
	// It will run until the user presses 'escape' or closes the window
	while( CGG::ProcessFrame() )
	{
		// Set every pixel to the same colour
		CGG::SetBackground( 0,0,0 );
		
		// Change our pixel's X coordinate according to time
		pixelX = (windowWidth / 2) + (int)(sin(timer) * 100.0f);
		// Update our time variable
		timer += 1.0f / 60.0f;

		// Draw the pixel to the screen
		CGG::DrawPixel( pixelX, pixelY, red, green, blue );

	}
	
	return 0;
	*/
	
}
