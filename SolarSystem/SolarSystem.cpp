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

    compileAndLinkShader("shader/multilight.vert", "shader/multilight.frag");

    glEnable(GL_DEPTH_TEST);

    view = glm::lookAt(glm::vec3(170.f,0.f,50.f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
    projection = glm::mat4(1.f);

    //glActiveTexture(GL_TEXTURE0);

    p.setUniform("Light.Intensity", glm::vec3(1.f,1.f,1.f) );
    glActiveTexture(GL_TEXTURE0);
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

    model = glm::mat4(1.f);
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

    setMatrices();
    Sun->loadTexture();
    Sun->renderPlanet();

    model = glm::mat4(1.f);
    model = glm::translate(model, glm::vec3(0.f, 0.f, 15.f));
    model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));

    setMatrices();
    Mercury->loadTexture();
    Mercury->renderPlanet();

    model = glm::mat4(1.f);
    model = glm::translate(model, glm::vec3(0.f, 0.f, 20.f));
    model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));

    setMatrices();
    Venus->loadTexture();
    Venus->renderPlanet();


    model = glm::mat4(1.f);
    model = glm::translate(model, glm::vec3(0.f, 0.f, 30.f));
    model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));

    setMatrices();
    Earth->loadTexture();
    Earth->renderPlanet();

    model = glm::mat4(1.f);
    model = glm::translate(model, glm::vec3(0.f, 0.f, 40.f));
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

    setMatrices();
    Mars->loadTexture();
    Mars->renderPlanet();

    model = glm::mat4(1.f);
    model = glm::translate(model, glm::vec3(0.f, 0.f, 50.f));
    model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));

    setMatrices();
    Jupiter->loadTexture();
    Jupiter->renderPlanet();

    model = glm::mat4(1.f);
    model = glm::translate(model, glm::vec3(0.f, 0.f, 60.f));
    model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));

    setMatrices();
    Saturn->loadTexture();
    Saturn->renderPlanet();

    model = glm::mat4(1.f);
    model = glm::translate(model, glm::vec3(0.f, 0.f, 70.f));
    model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));

    setMatrices();
    Uranus->loadTexture();
    Uranus->renderPlanet();

    model = glm::mat4(1.f);
    model = glm::translate(model, glm::vec3(0.f, 0.f, 80.f));
    model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));

    setMatrices();
    Neptune->loadTexture();
    Neptune->renderPlanet();
    glActiveTexture(GL_TEXTURE0);
}

void SolarSystem::renderMercury(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.f, 0.f, .0f, .0f);

    glActiveTexture(GL_TEXTURE0);
    //Sun->loadTexture();

    //p.setUniform("Light.Position", glm::vec4(0.0f,0.0f,0.0f,1.0f) );
    p.setUniform("Material.Kd", 0.9f, 0.9f, 0.9f);
    p.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
    p.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    p.setUniform("Material.Shininess", 100.0f);


}

// This procedure is called in the main loop!
void SolarSystem::update(float t){

}

void SolarSystem::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(45.0f), (float)w/h, 0.1f, 10000.0f);
}

void SolarSystem::setMatrices()
{
    glm::mat4 mv = view * model;
    p.setUniform("ModelViewMatrix", mv);
    p.setUniform("NormalMatrix",
                    glm::mat3( glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]) ));
    p.setUniform("MVP", projection * mv);
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