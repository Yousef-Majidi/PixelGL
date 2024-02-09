#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer.h"
#include "../Shapes/Rectangle/Rectangle.h"

Renderer::Renderer() {}

Renderer::~Renderer()
{
    
}

void Renderer::setNumVertices(GLuint numVertices)
{
    // m_numVertices = numVertices;
}

const Shader Renderer::getShader() const
{
    return m_shader;
}

void Renderer::initializeGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void Renderer::initializeGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
}

void Renderer::initializeShader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    this->m_shader = Shader(vertexShaderPath, fragmentShaderPath);
}

void Renderer::render(const GLuint VAO, const GLuint EBO, const GLuint numVertices)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, numVertices, GL_UNSIGNED_INT, 0);
}