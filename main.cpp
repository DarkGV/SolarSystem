#include <iostream>

#include "Planet.cpp"


void getMaxFlagfromRGB(bool maxFlag[], float RGB[3])
{
    float maxValue = RGB[0];
    for(int i = 1; i < 3; i ++)
    {
        if(maxValue < RGB[i])
            maxValue = RGB[i];
    }
    for(int i = 0; i < 3; i ++)
    {
        if(maxValue != 0 && maxValue == RGB[i])
            maxFlag[i] = true;
        else
            maxFlag[i] = false;
    }

}

void initPerspective(glm::mat4 & m)
{
    const float aspect = 1;
    const float zNear = 10.0f;
    const float zFar = -1.0f;
    const float zRange = zNear - zFar;
    const float tanHalfFOV = tanf(0.5);
    m[0][0] = 1.0f / (tanHalfFOV * aspect);
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = 1.0f / tanHalfFOV;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = (zNear + zFar) / (zNear - zFar);
    m[2][3] = 2.0f * zFar * zNear /  (zNear - zFar);
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = -1.0f;
    m[3][3] = 0.0f;
}

void initVAO()
{

	glGenVertexArrays(1, &GLMAIN::vao);
	glBindVertexArray(GLMAIN::vao);

    GLuint positionBufferHandle;
	glGenBuffers(1, &positionBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLMAIN::Verts), GLMAIN::Verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &GLMAIN::elementBufferHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  GLMAIN::elementBufferHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLMAIN::Faces), GLMAIN::Faces, GL_STATIC_DRAW);
}

int setShaders()
{
	GLint vertCompiled, fragCompiled;
	GLint tcsCompiled, tesCompiled, gsCompiled;


	GLint linked;
	char *vs = NULL, *fs = NULL;
	char *cs = NULL, *es = NULL, *gs = NULL;

	GLuint VertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);;
    	GLuint tcsObject = glCreateShader(GL_TESS_CONTROL_SHADER);
    	GLuint tesObject = glCreateShader(GL_TESS_EVALUATION_SHADER);
    	GLuint gsObject = glCreateShader(GL_GEOMETRY_SHADER);

	GLuint ProgramObject = glCreateProgram();

	vs = textFileRead((char *)"test.vert");   // vertex shader
	fs = textFileRead((char *)"test.frag");   // fragment shader
    	cs = textFileRead((char *)"test.cont");   // TCS shader
	es = textFileRead((char *)"test.eval");   // TES shader
	gs = textFileRead((char *)"test.gs");     // Geometry shader

	glUseProgram(ProgramObject);

	// Load source code into shaders.
	glShaderSource(VertexShaderObject, 1, (const char **)&vs, NULL);
	glShaderSource(FragmentShaderObject, 1, (const char **)&fs, NULL);

	glShaderSource(tcsObject, 1, (const char **)&cs, NULL);
	glShaderSource(tesObject, 1, (const char **)&es, NULL);
	glShaderSource(gsObject, 1, (const char **)&gs, NULL);

	// Compile the  vertex shader.
	glCompileShader(VertexShaderObject);
	glGetShaderiv(VertexShaderObject, GL_COMPILE_STATUS, &vertCompiled);
	// Compile the fragment shader
	glCompileShader(FragmentShaderObject);
	glGetShaderiv(FragmentShaderObject, GL_COMPILE_STATUS, &fragCompiled);
	// Compile the tessellation control shader
    	glCompileShader(tcsObject);
	glGetShaderiv(tcsObject, GL_COMPILE_STATUS, &tcsCompiled);
    	// Compile the tessellation evaluate shader
	glCompileShader(tesObject);
	glGetShaderiv(tesObject, GL_COMPILE_STATUS, &tesCompiled);
	// Compile the geometry shader
	glCompileShader(gsObject);
	glGetShaderiv(gsObject, GL_COMPILE_STATUS, &gsCompiled);

	if (!vertCompiled || !fragCompiled||!tcsCompiled || !tesCompiled||!gsCompiled)
	{
		printf("Shader compile failed, vertCompiled:%d, fragCompiled:%d, tcsCompiled:%d, tesCompiled:%d, gsCompiled:%d\n",
               vertCompiled, fragCompiled, tcsCompiled, tesCompiled, gsCompiled);
		return 0;
	}

	glAttachShader(ProgramObject, VertexShaderObject);
	glAttachShader(ProgramObject, FragmentShaderObject);
	glAttachShader(ProgramObject, tcsObject);
	glAttachShader(ProgramObject, tesObject);
	glAttachShader(ProgramObject, gsObject);

	glLinkProgram(ProgramObject);
	glGetProgramiv(ProgramObject, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		// Print logs if link shaders failed.
		GLsizei len;
		glGetProgramiv(ProgramObject, GL_INFO_LOG_LENGTH, &len);
		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(ProgramObject, len, &len, log);
		printf("Shader linking failed: %s\n", log);
		delete[] log;
		return 0;
	}

	glUseProgram(ProgramObject);


	GLMAIN::planetLocaionLoc = glGetUniformLocation(ProgramObject, "planetLocaion");
	GLMAIN::radiusLoc = glGetUniformLocation(ProgramObject, "radius");
	GLMAIN::planetColorLoc = glGetUniformLocation(ProgramObject, "planetColor");
	GLMAIN::mvpLoc = glGetUniformLocation(ProgramObject, "mvp");
	GLMAIN::mvLoc = glGetUniformLocation(ProgramObject, "mv");
	GLMAIN::lightAmbientLoc = glGetUniformLocation(ProgramObject, "La");  // //Ambient light intensity
	GLMAIN::reflectAmbientLoc = glGetUniformLocation(ProgramObject, "Ra"); //Ambient reflectivity
	GLMAIN::lightPosLoc = glGetUniformLocation(ProgramObject, "lightPos"); //Ambient reflectivity


	glDeleteShader(VertexShaderObject);
	glDeleteShader(FragmentShaderObject);
	glDeleteShader(tcsObject);
	glDeleteShader(tesObject);
	glDeleteShader(gsObject);
	glDeleteProgram(ProgramObject);
	return 1;
}

void keyfunc(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS )  // If space key is pressed, pause/resume animation
    {
        GLMAIN::paused = !GLMAIN::paused;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

    glViewport(0, 0, width, height);
    GLMAIN::frameBufferWidth = width;
    GLMAIN::frameBufferHeight = height;
}

/*
int main(){

  // Create on the heap memory
  Window* window = new Window(1024, "Sistema Solar");

  Render* render = new Render();

  Planet* p = new Planet(1.f, 36*5, 18*5);

  //render->loadShaders((char*)"shaders/vertex.glsl", (char*)"shaders/fragment.glsl");

  //glOrtho(-10.f, 10.f, -10.f, 10.f, -10.f, 10.f);

  glViewport(0, 0, 1024, 1024);

  render->transferData(p);

  while(!window->shouldClose()){
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render->draw();
    window->updateWindow();
  }

  return 0;
}
*/

int main(int argc, char* argv[])
{
	// init glfw
	if (!glfwInit())
		return -1;

	// create a windowed mode window and its OpenGL context
	GLMAIN::window = glfwCreateWindow(GLMAIN::frameBufferWidth, GLMAIN::frameBufferHeight, "Solar System", NULL, NULL);
	if (!GLMAIN::window)
	{
		glfwTerminate();
		return -1;
	}

	//make the window's context current
	glfwMakeContextCurrent(GLMAIN::window);
	glfwSetKeyCallback(GLMAIN::window,keyfunc);
	glfwSetFramebufferSizeCallback(GLMAIN::window, framebuffer_size_callback);

	// init glew
	glewExperimental = GL_TRUE;
	glewInit();

	setShaders();
	initVAO();

	static double limitFPS = 1.0 / 30.0; // limit to 30 frames per second
	double lastTime = glfwGetTime();
	double deltaTime = 0, nowTime = 0;

    glEnable(GL_DEPTH_TEST);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(GLMAIN::window))
	{
		nowTime = glfwGetTime();
		deltaTime += (nowTime - lastTime) / limitFPS;
		lastTime = nowTime;

		if (deltaTime < 1.0)
			continue;
		// - Only update at 30 frames / second
		while (deltaTime >= 1.0) {
			deltaTime--;
		}
		calcLocations();
		display(); //  Render function
	}
	glfwTerminate();
	return 0;
}