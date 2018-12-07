
#include <cmath>
#include "CGG_Main.h"
#include "Scene.h"

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

	Scene scene;

	scene.Init(windowWidth,windowHeight);

	scene.Render();

	return CGG::ShowAndHold();
}

