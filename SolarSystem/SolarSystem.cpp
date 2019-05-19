#include "SolarSystem.hpp"

SolarSystem::SolarSystem(){
    Sun = new Planet("/Users/DiogoSilva/Desktop/CGPratico/res/Sun/SunObject.obj", "/Users/DiogoSilva/Desktop/CGPratico/res/Sun/SunTexture.jpg");
    Mercury = new Planet("/Users/DiogoSilva/Desktop/CGPratico/res/Mercury/MercuryObject.obj", "/Users/DiogoSilva/Desktop/CGPratico/res/Mercury/MercuryTexture.jpg");
    Venus = new Planet("/Users/DiogoSilva/Desktop/CGPratico/res/Venus/VenusObject.obj", "/Users/DiogoSilva/Desktop/CGPratico/res/Venus/VenusTexture.jpg");
    Earth = new Planet("/Users/DiogoSilva/Desktop/CGPratico/res/Earth/EarthObject.obj", "/Users/DiogoSilva/Desktop/CGPratico/res/Earth/EarthTexture.jpg");
    Mars = new Planet("/Users/DiogoSilva/Desktop/CGPratico/res/Mars/MarsObject.obj", "/Users/DiogoSilva/Desktop/CGPratico/res/Mars/MarsTexture.jpg");
    Jupiter = new Planet("/Users/DiogoSilva/Desktop/CGPratico/res/Jupiter/JupiterObject.obj", "/Users/DiogoSilva/Desktop/CGPratico/res/Jupiter/JupiterTexture.jpg");
    Saturn = new Planet("/Users/DiogoSilva/Desktop/CGPratico/res/Saturn/SaturnObject.obj", "/Users/DiogoSilva/Desktop/CGPratico/res/Saturn/SaturnTexture.jpg");
    Uranus = new Planet("/Users/DiogoSilva/Desktop/CGPratico/res/Uranus/UranusObject.obj", "/Users/DiogoSilva/Desktop/CGPratico/res/Uranus/UranusTexture.jpg");
    Neptune = new Planet("/Users/DiogoSilva/Desktop/CGPratico/res/Neptune/NeptuneObject.obj", "/Users/DiogoSilva/Desktop/CGPratico/res/Neptune/NeptuneTexture.jpg");
}

// Static definition of components
void SolarSystem::initScene(){

    compileAndLinkShader("shader/SolarSystem.vert", "shader/multilight.frag");

    glEnable(GL_DEPTH_TEST);

    view = glm::lookAt(glm::vec3(150.f,30.f,-150.f), glm::vec3(0.0f,0.0f, 0.0f), glm::vec3(0.0f,1.0f,0.0f));
    projection = glm::mat4(1.f);

    p.setUniform("Light.Intensity", glm::vec3(1.f,1.f,1.f) );
    glActiveTexture(GL_TEXTURE0);

    /**
     * Here planets run at real speed scaled at 1/1000000
     */
    Sun->setPlanetOptions(3.f, 0.f, 0.f, 0.f);
    Mercury->setPlanetOptions(2.4397f, 0.4787, 0.f, 57.91f);
    Venus->setPlanetOptions(6.0518f, 0.3502f, 0.f, 108.2f);
    Earth->setPlanetOptions(6.371f, 0.2978f, 0.f, 149.6f);
    Mars->setPlanetOptions(3.3895f,0.24077f, 0.f, 227.9f);
    Jupiter->setPlanetOptions(69.911f, 0.1307f, 0.f, 778.5f);
    Saturn->setPlanetOptions(58.232f, 0.0969f, 0.f, 1434.f);
    Uranus->setPlanetOptions(25.362f, 0.0681f, 0.f, 2871.f);
    Neptune->setPlanetOptions(24.622f, 0.0543f, 0.f,4495.f);

}

// This procedure is always called on mainLoop
void SolarSystem::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.f, 0.f, .0f, .0f);

    p.setUniform("Light.Position", glm::vec4(0.0f,.0f,0.0f,1.0f) );
    p.setUniform("Material.Kd", 0.9f, 0.9f, 0.9f);
    p.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
    p.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    p.setUniform("Material.Shininess", 100.0f);

    setMatrices(Sun->planetModel);
    Sun->loadTexture();
    Sun->renderPlanet();

    setMatrices(Mercury->planetModel);
    Mercury->loadTexture();
    Mercury->renderPlanet();


    setMatrices(Venus->planetModel);
    Venus->loadTexture();
    Venus->renderPlanet();


    setMatrices(Earth->planetModel);
    Earth->loadTexture();
    Earth->renderPlanet();

    setMatrices(Mars->planetModel);
    Mars->loadTexture();
    Mars->renderPlanet();


    setMatrices(Jupiter->planetModel);
    Jupiter->loadTexture();
    Jupiter->renderPlanet();

    setMatrices(Saturn->planetModel);
    Saturn->loadTexture();
    Saturn->renderPlanet();

    setMatrices(Uranus->planetModel);
    Uranus->loadTexture();
    Uranus->renderPlanet();

    setMatrices(Neptune->planetModel);
    Neptune->loadTexture();
    Neptune->renderPlanet();
    view = glm::lookAt(Earth->position, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
}

// This procedure is called in the main loop!
void SolarSystem::update(float t){

    // Time elapses approx 0.3 s

    /**
     * Sun rotational speed is about 1997 km/s
     * We'll get
     * 1997 - 1
     *   x  - 0.3
     */
    Sun->planetModel = glm::scale(glm::mat4(1.f), glm::vec3(0.1f, 0.1f, 0.1f));
    Sun->planetModel = glm::rotate(Sun->planetModel, glm::radians(t*1997), glm::vec3(0.0f, 1.0f, 0.0f));

    /**
     * Mercury spins at speed of 10.83 Km/h
     */
    Mercury->movePlanet();
    Mercury->planetModel = glm::scale(Mercury->planetModel, glm::vec3(0.01f, 0.01f, 0.01f));
    Mercury->planetModel = glm::rotate(Mercury->planetModel, glm::radians(t*10.83f/60.f), glm::vec3(0.0f, 1.0f, 0.0f));


    /**
     * Venus spins at speed of 6.52 km/h
     */
    Venus->movePlanet();
    Venus->planetModel = glm::scale(Venus->planetModel, glm::vec3(0.01f, 0.01f, 0.01f));
    Venus->planetModel = glm::rotate(Venus->planetModel, glm::radians(t*6.52f/60.f), glm::vec3(0.0f, 1.0f, 0.0f));

    /**
     * Earth's rotation speed is 1674 km/h
     */ 
    Earth->movePlanet();
    Earth->planetModel = glm::rotate(Earth->planetModel, glm::radians(t*1674.f/60.f), glm::vec3(0.0f, 1.0f, 0.0f));
    Earth->planetModel = glm::scale(Earth->planetModel, glm::vec3(0.003f, 0.003f, 0.003f));

    /**
     * Mars spins at speed 866 km/h
     */
    Mars->movePlanet();
    Mars->planetModel = glm::scale(Mars->planetModel, glm::vec3(0.1f, 0.1f, 0.1f));
    Mars->planetModel = glm::rotate(Mars->planetModel, glm::radians(t*866.f/60.f), glm::vec3(0.0f, 1.0f, 0.0f));

    /**
     * Jupiter spins at speed of 45583 km/h
     */
    Jupiter->movePlanet();
    Jupiter->planetModel = glm::scale(Jupiter->planetModel, glm::vec3(0.05f, 0.05f, 0.05f));
    Jupiter->planetModel = glm::rotate(Jupiter->planetModel, glm::radians(t*45583.f/60.f), glm::vec3(0.0f, 1.0f, 0.0f));

    /**
     * Saturn spins at speed of 36840 km/h
     */
    Saturn->movePlanet();
    Saturn->planetModel = glm::scale(Saturn->planetModel, glm::vec3(0.03f, 0.03f, 0.03f));
    Saturn->planetModel = glm::rotate(Saturn->planetModel, glm::radians(t*36840.f / 60.f), glm::vec3(0.0f, 1.0f, 0.0f));

    /**
     * Uranus spins at speed of 14794 km/h
     */
    Uranus->movePlanet();
    Uranus->planetModel = glm::scale(Uranus->planetModel, glm::vec3(0.03f, 0.03f, 0.03f));
    Uranus->planetModel = glm::rotate(Uranus->planetModel, glm::radians(t*14794.f/60.f), glm::vec3(0.0f, 1.0f, 0.0f));

    /**
     * Neptune spins at speed of 9719 km/h
     */
    Neptune->movePlanet();
    Neptune->planetModel = glm::scale(Neptune->planetModel, glm::vec3(0.03f, 0.03f, 0.03f));
    Neptune->planetModel = glm::rotate(Neptune->planetModel, glm::radians(t*9719.f/60.f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void SolarSystem::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(70.0f), (float)w/h, 0.1f, 10000.0f);
}

void SolarSystem::setMatrices(glm::mat4 model)
{
    p.setUniform("model", model);
    p.setUniform("view", view);
    p.setUniform("projection", projection);
}

void SolarSystem::compileAndLinkShader(std::string verticeShader, std::string fragmentShader)
{
	try {
		p.compileShader(verticeShader.c_str());
		p.compileShader(fragmentShader.c_str());
    	p.link();
    	p.use();
    } catch(GLSLProgramException & e) {
 		std::cerr << e.what() << std::endl;
 		exit( EXIT_FAILURE );
    }
}
void SolarSystem::keyfunc(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_SPACE)
        std::cout << "Espaço pressionado" << std::endl;
}