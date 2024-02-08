#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "App.h"
#include "../Shader/shaderinit.h"

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

void App::addShape(const Shape& shape)
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
    //float vertices[] = {
    //     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
    //     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
    //    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
    //    -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f // top left 
    //};
    //unsigned int indices[] = {
    //    0, 1, 3,  // first Triangle
    //    1, 2, 3   // second Triangle
    //};
    float vertices[] = {
        // Rectangle 1 (Top Right)
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.5f, // top right
        0.7f,  1.0f, 0.0f, 1.0f, 1.0f, 0.5f, // top right
        0.7f,  0.7f, 0.0f, 1.0f, 1.0f, 0.5f, // bottom right
        1.0f,  0.7f, 0.0f, 1.0f, 1.0f, 0.5f, // bottom right

        // Rectangle 2 (Bottom Right)
        1.0f, -0.7f, 0.0f, 1.0f, 1.0f, 0.5f, // top right
        0.7f, -0.7f, 0.0f, 1.0f, 1.0f, 0.5f, // top right
        0.7f, -1.0f, 0.0f, 1.0f, 1.0f, 0.5f, // bottom right
        1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.5f, // bottom right

        // Rectangle 3 (Bottom Left)
        -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.5f, // top left
        -0.7f, -1.0f, 0.0f, 1.0f, 1.0f, 0.5f, // top left
        -0.7f, -0.7f, 0.0f, 1.0f, 1.0f, 0.5f, // bottom left
        -1.0f, -0.7f, 0.0f, 1.0f, 1.0f, 0.5f, // bottom left

        // Rectangle 4 (Top Left)
        -1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.5f, // top left
        -0.7f,  1.0f, 0.0f, 1.0f, 1.0f, 0.5f, // top left
        -0.7f,  0.7f, 0.0f, 1.0f, 1.0f, 0.5f, // bottom left
        -1.0f,  0.7f, 0.0f, 1.0f, 1.0f, 0.5f// bottom left
    };

    unsigned int indices[] = {
        0, 1, 2,  // first Triangle
        2, 3, 0,   // second Triangle

        4, 5, 6,  // third Triangle
        6, 7, 4,   // fourth Triangle

        8, 9, 10,  // fifth Triangle
        10, 11, 8, // sixth Triangle

        12, 13, 14, // seventh Triangle
        14, 15, 12 // eighth Triangle
    };

    std::vector<float> verticesVec(vertices, vertices + sizeof(vertices) / sizeof(float));
    std::vector<unsigned int> indicesVec(indices, indices + sizeof(indices) / sizeof(unsigned int));

    Shape rectangle(verticesVec, indicesVec);
    addShape(rectangle);
    
    m_renderer->init(rectangle);
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
    for (const Shape& shape : m_shapes)
    {
        m_renderer->render();
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