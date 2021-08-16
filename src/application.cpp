#include "application.hpp"

Application::Application()
{}

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

     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }  

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    m_model = new Model("src/res/backpack/backpack.obj");
    m_shader = new Shader("src/shaders/shader.vs", "src/shaders/shader.fs");
    m_camera = new Camera();

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

}

void Application::updateState()
{

}

void Application::render()
{
    // Clear background
    glClearColor(0.3f, 0.6f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    m_shader->use();

    glm::mat4 projection = glm::perspective(glm::radians(m_camera->Zoom), (float)WINDOW_WIDTH/ (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = m_camera->GetViewMatrix();
    m_shader->setMat4("projection", glm::value_ptr(projection));
    m_shader->setMat4("view", glm::value_ptr(view));

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    m_shader->setMat4("model", glm::value_ptr(model));

    m_model->Draw(*m_shader); 
    
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow* m_window, int width, int height)
{
    glViewport(0, 0, width, height);
}



