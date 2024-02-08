#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "App.h"
#include "../Shader/shaderinit.h"
#include "../Shapes/Rectangle/Rectangle.h"

using std::string;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

App::App(unsigned int width, unsigned int height, const char* vertextShaderPath, const char* fragmentShaderPath) : m_width(width), m_height(height), m_vertexShaderPath(vertextShaderPath), m_fragmentShaderPath(fragmentShaderPath)
{
    m_renderer = std::make_unique<Renderer>();
    m_renderer->initializeGLFW();
    createWindow(this->m_width, this->m_height);
    m_renderer->initializeGLAD();
    m_renderer->initializeShader(m_vertexShaderPath, m_fragmentShaderPath);
    init();
}

App::~App()
{
    if (this->m_window)
    {
        glfwDestroyWindow(this->m_window);
        glfwTerminate();
    }
}

void App::run()
{
    gameLoop();
}

void App::addShape(const Rectangle& shape)
{
    m_shapes.push_back(shape);
}

void App::createWindow(unsigned int screenWidth, unsigned int screenHeight)
{
    this->m_window = glfwCreateWindow(screenWidth, screenHeight, "Scene", NULL, NULL);
    if (!m_window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(this->m_window);
    glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);
}

void App::init()
{
    Rectangle rectangle1(1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f, 1.0f); // 
    m_shapes.push_back(rectangle1);

    Rectangle rectangle2(1.0f, -0.7f, 0.0f, 1.0f, 1.0f, 0.5f, 1.0f); // 
    m_shapes.push_back(rectangle2);

    Rectangle rectangle3(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f, 1.0f); // 
    m_shapes.push_back(rectangle3);

    Rectangle rectangle4(0.0f, -0.5f, 0.0f, 1.0f, 1.0f, 0.5f, 1.0f); // 
    m_shapes.push_back(rectangle3);
}

void App::gameLoop()
{
    while (!glfwWindowShouldClose(this->m_window))
    {
        processInput(this->m_window);
        transform(m_renderer->getShader());
        render();
        glfwSwapBuffers(this->m_window);
        glfwPollEvents();
    }
}

void App::render()
{
    static const float black[] = { 1.0f, 0.0f, 0.0f, 0.0f };
    glClearBufferfv(GL_COLOR, 0, black);
    glClear(GL_COLOR_BUFFER_BIT);
    for (const Rectangle& shape : m_shapes)
    {
        m_renderer->render(shape);
    }
}

void App::transform(Shader shader)
{
    glm::mat4 transform = glm::mat4(1.0f);
    
    shader.use();
    unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void App::processInput(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: viewport to window adjustment
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}