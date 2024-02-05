#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGLApp.h"
#include "shader/shaderinit.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

OpenGLApp::OpenGLApp(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}

OpenGLApp::~OpenGLApp()
{
    if (this->m_window)
    {
        glfwDestroyWindow(this->m_window);
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
        glfwTerminate();
    }
}

void OpenGLApp::run()
{
    initializeGLFW();
    createWindow(this->m_width, this->m_height);
    initializeGLAD();
    initializeShader();
    init();
    gameLoop();
}

void OpenGLApp::initializeGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void OpenGLApp::createWindow(unsigned int screenWidth, unsigned int screenHeight)
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

void OpenGLApp::initializeGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
}

void OpenGLApp::initializeShader()
{
    this->m_shader = Shader("shader.vs", "shader.fs");
}

void OpenGLApp::init()
{
    float vertices[] = {
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    
    // determine the number of vertices
    this->m_numVertices = sizeof(indices) / sizeof(indices[0]);

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute pointer
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void OpenGLApp::gameLoop()
{
    while (!glfwWindowShouldClose(this->m_window))
    {
        processInput(this->m_window);
        transform(m_shader);
        render();
        glfwSwapBuffers(this->m_window);
        glfwPollEvents();
    }
}

void OpenGLApp::render()
{
    static const float black[] = {1.0f, 0.0f, 0.0f, 0.0f };
    glClearBufferfv(GL_COLOR, 0, black);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, m_numVertices, GL_UNSIGNED_INT, 0);
}

void OpenGLApp::transform(Shader shader)
{
    glm::mat4 transform = glm::mat4(1.0f);
    
    shader.use();
    unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void OpenGLApp::processInput(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: viewport to window adjustment
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}