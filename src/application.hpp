#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model.hpp"
#include "shader.hpp"
#include "camera.hpp"

#include <iostream>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_NAME "3d graphics"

class Application
{
public:
    Application();
    int create();
    void run();
private:
    GLFWwindow *m_window;
    Camera *m_camera;
    Model *m_model;
    Shader *m_shader;
    
private:
    void handleInput();
    void updateState();
    void render();
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif
