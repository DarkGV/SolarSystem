#include "scene.h"
#include "scenerunner.h"
//#include "SolarSystem.hpp"


int main(int argc, char *argv[])
{
	/**
	 * Main just calls SceneRunner to run the project.
	 */
	SceneRunner runner("Solar System");
	return runner.run( *( std::unique_ptr<Scene>( new SolarSystem() ) ) );
}
