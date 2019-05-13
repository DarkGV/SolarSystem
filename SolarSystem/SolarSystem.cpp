#include "SolarSystem.hpp"

SolarSystem::SolarSystem(){
    Sun = new Planet("/Users/DiogoSilva/Desktop/CGPratico/res/Sun/SunObject.obj", "/Users/DiogoSilva/Desktop/CGPratico/res/Sun/SunTexture.jpg");
}

// Static definition of components
void SolarSystem::initScene(){

    compileAndLinkShader("shader/multilight.vert", "shader/multilight.frag");

    glEnable(GL_DEPTH_TEST);

    view = glm::lookAt(glm::vec3(130.f,0.f,-10.f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
    projection = glm::mat4(1.f);

    Sun->loadTexture();

    p.setUniform("Light.Intensity", glm::vec3(1.f,1.f,1.f) );
}

// This procedure is always called on mainLoop
void SolarSystem::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    p.setUniform("Light.Position", glm::vec4(0.0f,0.0f,0.0f,1.0f) );
    p.setUniform("Material.Kd", 0.9f, 0.9f, 0.9f);
    p.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
    p.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    p.setUniform("Material.Shininess", 100.0f);

    model = glm::mat4(1.f);

    setMatrices();
    Sun->renderPlanet();    
}

// This procedure is called in the main loop!
void SolarSystem::update(float t){

}

void SolarSystem::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(70.0f), (float)w/h, 0.3f, 100.0f);
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