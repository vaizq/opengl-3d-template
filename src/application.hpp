#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "body.hpp"
#include "shader.hpp"
#include "camera.hpp"

#include <iostream>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_NAME "3d graphics"

struct Mouse
{
    float posX;
    float posY;
    bool posInited = false;
};

class Application
{
public:
    Application();
    int create();
    void run();
private:
    GLFWwindow *m_window;
    Camera *m_camera;
    Body *m_body;
    Shader *m_shader;

    Mouse m_mouse;

    float m_deltaTime;
    float m_lastTime;

    float mousePosX;
    float mousePosY;
    bool initMousePos = false;
    
private:
    void handleInput();
    void updateState();
    void render();
    void calcDeltaTime();

    // Callbacks
    void setCallbackFunctions();
    void mousePosCallback(GLFWwindow* window, double posX, double posY);
    void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    class GLFWCallbackWrapper
    {
        public:
            GLFWCallbackWrapper() = delete;
            GLFWCallbackWrapper(const GLFWCallbackWrapper&) = delete;
            GLFWCallbackWrapper(GLFWCallbackWrapper&&) = delete;
            ~GLFWCallbackWrapper() = delete;

            static void MousePositionCallback(GLFWwindow* window, double positionX, double positionY);
            static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void SetApplication(Application *application);
        private:
            static Application* s_application;
    };
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif
