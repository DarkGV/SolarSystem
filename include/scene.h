#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Scene
{
protected:
	glm::mat4 model, view, projection;

public:
    int width;
    int height;
    static Scene *event_handling;

	Scene() : width(800), height(600) { }
	virtual ~Scene() {}

	void setDimensions( int w, int h ) {
	    width = w;
	    height = h;
	}
	
    /**
      Load textures, initialize shaders, etc.
      */
    virtual void initScene() = 0;

    /**
      This is called prior to every frame.  Use this
      to update your animation.
      */
    virtual void update( float t ) = 0;

    /**
      Draw your scene.
      */
    virtual void render() = 0;

    virtual void keycallback(GLFWwindow*, int, int, int, int) = 0;
    virtual void mousecallback(GLFWwindow*, double, double) = 0;

    virtual void setEventHandling() { event_handling = this; }

    /**
      Called when screen is resized
      */
    virtual void resize(int, int) = 0;

    static void keycallback_event(GLFWwindow* window, int key, int scancode, int action, int mods){
      if(event_handling)
        event_handling->keycallback(window, key, scancode, action, mods);
    }

    static void mousecallback_event(GLFWwindow *window , double xpos, double ypos){
      if(event_handling)
        event_handling->mousecallback(window, xpos,ypos);
    }
};
