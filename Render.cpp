#include "include/Render.hpp"
#include <common/shader.cpp>

Render::Render(){
  glewExperimental = true;

  if(glewInit() != GLEW_OK) 
    throw "Couldn't initiate GLEW";
  
  programID = LoadShaders((char*)"shaders/vertex.glsl", (char*)"shaders/fragment.glsl");
  glGenVertexArrays(1, &(this->VertexArrayObject));
  glGenVertexArrays(1, &(this->ElementBufferObject));
  glGenVertexArrays(1, &(this->VertexBufferObject));

}

void Render::transferData(Planet* p){

  Planets.push_back(p);

  glUseProgram(programID);

  glBindVertexArray(this->VertexArrayObject);

  glBindBuffer(GL_ARRAY_BUFFER, this->VertexBufferObject);
  glBufferData(GL_ARRAY_BUFFER, (unsigned int)p->planetVertices.size() * sizeof(float), p->planetVertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ElementBufferObject);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, (unsigned int)p->planetIndices.size() * sizeof(unsigned int), p->planetIndices.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glDisableVertexAttribArray(0);

}

void Render::draw(){
  glBindVertexArray(this->VertexArrayObject);

  glm::mat4 projection = glm::perspective(glm::radians<float>(90), 4.f/3.f, 10.f, 10000.0f);
  glm::mat4 view = glm::lookAt(
								glm::vec3(4,3,-3), // Camera is at (4,3,-3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
);
  glm::mat4 model = glm::mat4(1.f);

  GLint mvpLocation = glGetUniformLocation(programID, "MVP");

  std::cout << mvpLocation;

  glm::mat4 mvp = projection * view * model;

  glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);

  for(int i = 0; i < Planets.size(); i++){
    Planet* p = Planets[i];
    glDrawArrays(GL_LINE_LOOP, 0, (unsigned int) p->planetVertices.size()*sizeof(float));
  }
}

/*
void Render::loadShaders(char* vertexShader_file, char* fragmentShader_file){

  // Create shaders first
  GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

  // Next we load shaders into memory. Preparing to compile

  std::string vertexShader;
  std::ifstream vertexShaderStream(vertexShader_file, std::ios::in);

  if(vertexShaderStream.is_open()){
    std::stringstream vertexShaderContent;
    vertexShaderContent << vertexShaderStream.rdbuf();
    vertexShader = vertexShaderContent.str();
    vertexShaderStream.close();
  }
  else
    throw "Error loading vertex shader";
  
  std::string fragmentShader;
  std::ifstream fragmentShaderStream(fragmentShader_file, std::ios::in);

  if(fragmentShaderStream.is_open()){
    std::stringstream fragmentShaderContent;
    fragmentShaderContent << fragmentShaderStream.rdbuf();
    fragmentShader = fragmentShaderContent.str();
    fragmentShaderStream.close();
  }

  const char* vertexShaderPointer = vertexShader.c_str();
  glShaderSource(vertexShaderID, 1, &vertexShaderPointer, NULL);
  glCompileShader(vertexShaderID);

  const char* fragmentShaderPointer = fragmentShader.c_str();
  glShaderSource(fragmentShaderID, 1, &fragmentShaderPointer, NULL);
  glCompileShader(fragmentShaderID);

  programID = glCreateProgram();
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID);

  glDetachShader(programID, vertexShaderID);
  glDetachShader(programID, fragmentShaderID);

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);
}
*/