#include "application.hpp"


Application::Application()
{
    Application::GLFWCallbackWrapper::SetApplication(this);
}

int Application::create()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);
    if( m_window == NULL )
    {

        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(m_window);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }  

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);

    m_model = new Model("src/res/backpack/backpack.obj");
    m_shader = new Shader("src/shaders/shader.vs", "src/shaders/shader.fs");
    m_camera = new Camera();

    setCallbackFunctions();

    return 0;
}

void Application::run()
{
    while(!glfwWindowShouldClose(m_window))
    {
        handleInput();
        updateState();
        render();
    }
}

void Application::handleInput()
{
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }

    if(glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_camera->ProcessKeyboard(FORWARD, m_deltaTime);
    }
    if(glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    {
        m_camera->ProcessKeyboard(BACKWARD, m_deltaTime);
    }
    if(glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_camera->ProcessKeyboard(LEFT, m_deltaTime);
    }
    if(glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_camera->ProcessKeyboard(RIGHT, m_deltaTime);
    }
}

void Application::updateState()
{

}

void Application::render()
{
    calcDeltaTime();

    // Clear background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    m_shader->use();

    glm::mat4 projection = glm::perspective(glm::radians(m_camera->Zoom), (float)WINDOW_WIDTH/ (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = m_camera->GetViewMatrix();
    m_shader->setMat4("projection", glm::value_ptr(projection));
    m_shader->setMat4("view", glm::value_ptr(view));

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.5f)); // translate it down so it's at the center of the scene
    model = glm::rotate(model, 1.1f, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
    m_shader->setMat4("model", glm::value_ptr(model));

    m_model->Draw(*m_shader); 
    
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void Application::calcDeltaTime()
{
    float curTime = glfwGetTime();
    m_deltaTime = curTime - m_lastTime;
    m_lastTime = curTime;
}
// Callback functions
void Application::mousePosCallback(GLFWwindow* window, double posX, double posY)
{
    if(!m_mouse.posInited)
    {
        m_mouse.posX = posX;
        m_mouse.posY = posY;
        m_mouse.posInited = true;
    }
    else
    {
        float offsetX = posX - m_mouse.posX; 
        float offsetY = posY - m_mouse.posY;
        m_camera->ProcessMouseMovement(offsetX, offsetY);
        m_mouse.posX = posX;
        m_mouse.posY = posY;
    }
}
void Application::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}
void Application::setCallbackFunctions()
{
    GLFWCallbackWrapper::SetApplication(this);
    glfwSetCursorPosCallback(m_window, GLFWCallbackWrapper::MousePositionCallback);
    glfwSetKeyCallback(m_window, GLFWCallbackWrapper::KeyboardCallback);
}


// Callback wrappers functions 
void Application::GLFWCallbackWrapper::MousePositionCallback(GLFWwindow* window, double positionX, double positionY)
{
    s_application->mousePosCallback(window, positionX, positionY);
}

void Application::GLFWCallbackWrapper::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    s_application->keyboardCallback(window, key, scancode, action, mods);
}

Application* Application::GLFWCallbackWrapper::s_application = nullptr;

void Application::GLFWCallbackWrapper::SetApplication(Application *application)
{
    GLFWCallbackWrapper::s_application = application;
}

void framebuffer_size_callback(GLFWwindow* m_window, int width, int height)
{
    glViewport(0, 0, width, height);
}



