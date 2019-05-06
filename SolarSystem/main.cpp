#include "scene.h"
#include "scenerunner.h"
#include "scenemultilight.h"


int main(int argc, char *argv[])
{

	SceneRunner runner("Chapter 3 - ");
	std::unique_ptr<Scene> scene;
	scene = std::unique_ptr<Scene>( new SceneMultiLight() );

	return runner.run(*scene);
}
