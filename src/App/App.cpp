#include <cstdlib>
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

/************DEBUG*************/
static unsigned int RAND = NULL;
static bool ROTATE = false;
static bool SCALE = false;
static bool MOVE = false;
static float R_ANGLE = 45.0f;
static float S_FACTOR = 2.5f;
/************DEBUG*************/

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
    glfwSetWindowUserPointer(this->m_window, this);
    glfwSetKeyCallback(this->m_window, keyCallback);
    glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);
}

void App::init()
{
    /**************************************************/
    /*****************ADD SHAPES HERE******************/
    /**************************************************/

    // blue shape at the center
    /*glm::vec3 coordinates = glm::vec3(0.0f, 0.0f, 0.0f);
    float size = 0.3f;
    glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
    Rectangle rectangle1(coordinates, size, color);
    m_shapes.push_back(rectangle1);*/

    // purple
    glm::vec3 coordinates = glm::vec3(-0.85f, 0.85f, 0.0f);
    float size = 0.3f;
    glm::vec3 color = glm::vec3(0.412f, 0.141f, 0.859f);
    Rectangle rectangle1(coordinates, size, color); 
    m_shapes.push_back(rectangle1);

    // pink 
    glm::vec3 coordinates2 = glm::vec3(0.85f, 0.85f, 0.0f);
    float size2 = 0.3f;
    glm::vec3 color2 = glm::vec3(0.949f, 0.141f, 0.765f);
    Rectangle rectangle2(coordinates2, size2, color2);
    m_shapes.push_back(rectangle2);

    // yellow
    glm::vec3 coordinates3 = glm::vec3(-0.85f, -0.85f, 0.0f);
    float size3 = 0.3f;
    glm::vec3 color3 = glm::vec3(0.949f, 0.875f, 0.141f);
    Rectangle rectangle3(coordinates3, size3, color3);
    m_shapes.push_back(rectangle3);

    // green
    glm::vec3 coordinates4 = glm::vec3(0.85f, -0.85f, 0.0f);
    float size4 = 0.3f;
    glm::vec3 color4 = glm::vec3(0.259f, 0.459f, 0.318f);
    Rectangle rectangle4(coordinates4, size4, color4);
    m_shapes.push_back(rectangle4);
}

void App::gameLoop()
{
    while (!glfwWindowShouldClose(this->m_window))
    {
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
    for (Rectangle& shape : m_shapes)
    {
        if (ROTATE && &shape == &m_shapes.at(RAND))
        {
            shape.rotate(R_ANGLE);
        }

        if (SCALE && &shape == &m_shapes.at(RAND))
        {
            shape.scale(S_FACTOR);
        }

        if (MOVE && &shape == &m_shapes.at(RAND))
        {
            glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
            shape.moveTo(center);
        }

        // Reset transform and scale if none of ROTATE, SCALE, or MOVE is true
        if (!SCALE)
        {
            shape.resetScale();
        }
        if (!ROTATE)
        {
            shape.resetTransform();
        }
        if (!MOVE)
        {
			shape.resetPosition();
		}

        m_renderer->getShader().use();
        unsigned int transformLoc = glGetUniformLocation(m_renderer->getShader().ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(shape.getTransform()));
        m_renderer->render(shape.getVAO(), shape.getEBO(), shape.getNumVertices());
    }
}

void App::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
		glfwSetWindowShouldClose(window, true);
        std::cout << "Exiting the game..." << std::endl;
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        RAND = rand() % 4;
		std::cout << "New index selected: " << RAND << std::endl;
	}

    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        ROTATE = !ROTATE;
		std::cout << "Rotate: " << ROTATE << " - at index " << RAND << std::endl;
	}

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
		SCALE = !SCALE;
		S_FACTOR = SCALE ? 2.5f : 1.0f;
        std::cout << "Scale: " << SCALE << " - at index " << RAND << std::endl;
    }

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        MOVE = !MOVE;
        std::cout << "Move: " << MOVE << " - at index " << RAND << std::endl;
    }
}

// glfw: viewport to window adjustment
void App::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
