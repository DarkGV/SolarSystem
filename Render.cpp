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

  glBindVertexArray(this->VertexArrayObject);

  glBindBuffer(GL_ARRAY_BUFFER, this->VertexBufferObject);
  glBufferData(GL_ARRAY_BUFFER, (unsigned int)p->planetVertices.size() * sizeof(float), p->planetVertices.data(), GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ElementBufferObject);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, (unsigned int)p->planetIndices.size() * sizeof(unsigned int), p->planetIndices.data(), GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

}

void Render::draw(){
  glUseProgram(programID);
  glBindVertexArray(this->VertexArrayObject);
  for(int i = 0; i < Planets.size(); i++){
    Planet* p = Planets[i];
    glDrawElements(GL_TRIANGLES, (unsigned int) p->planetIndices.size(), GL_UNSIGNED_INT, NULL);
  }
  glBindVertexArray(0);
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