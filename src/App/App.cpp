#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "../Renderer/Renderer.h"
#include "../Shader/shaderinit.h"
#include "../Shapes/Rectangle/Rectangle.h"
#include "App.h"

using std::string;

App::App(unsigned int width, unsigned int height, const char* vertextShaderPath, const char* fragmentShaderPath) : m_vertexShaderPath(vertextShaderPath), m_fragmentShaderPath(fragmentShaderPath)
{
    m_renderer = std::make_unique<Renderer>();
    m_renderer->initializeGLFW();
    createWindow(width, height);
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
    /**************************************************/
    /*****************ADD SHAPES HERE******************/
    /**************************************************/

    // red
    glm::vec3 coordinates = glm::vec3(0.0f, 0.0f, 0.0f);
    float size = 0.5f;
    glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
    Rectangle rectangle1(coordinates, size, color); 
    m_shapes.push_back(rectangle1);

    // pink 
    glm::vec3 coordinates2 = glm::vec3(0.85f, 0.85f, 0.0f);
    float size2 = 0.3f;
    glm::vec3 color2 = glm::vec3(1.0f, 0.0f, 1.0f);
    Rectangle rectangle2(coordinates2, size2, color2);
    m_shapes.push_back(rectangle2);

    // yellow
    glm::vec3 coordinates3 = glm::vec3(-0.7f, -0.7f, 0.0f);
    float size3 = 0.2f;
    glm::vec3 color3 = glm::vec3(1.0f, 1.0f, 0.0f);
    Rectangle rectangle3(coordinates3, size3, color3);
    m_shapes.push_back(rectangle3);

    // green
    glm::vec3 coordinates4 = glm::vec3(0.7f, -0.7f, 0.0f);
    float size4 = 0.1f;
    glm::vec3 color4 = glm::vec3(0.0f, 1.0f, 0.0f);
    Rectangle rectangle4(coordinates4, size4, color4);
    m_shapes.push_back(rectangle4);
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
        m_renderer->render(shape.getVAO(), shape.getEBO(), shape.getNumVertices());
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
void App::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
