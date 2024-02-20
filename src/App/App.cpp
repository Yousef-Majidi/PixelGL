#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "../Color/Color.h"
#include "../Renderer/Renderer.h"
#include "../Shader/shaderinit.h"
#include "../Shapes/Rectangle/Rectangle.h"
#include "App.h"

using std::string;

/************DEBUG*************/
static unsigned int RAND = 0;
static bool ROTATE = false;
static bool SCALE = false;
static bool MOVE = false;
static bool RESET = false;
static float R_ANGLE = 5.0f;
static float S_FACTOR = 1.0f;
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

	float leftEdge = -0.90f;
	float rightEdge = 0.90f;
	float size = 0.2f;
	float step = size;
	int row = 0;
	Color borderColor = Color::WHITE;

	Color colors[6] = {
		Color::YELLOW,
		Color::BLUE,
		Color::CYAN,
		Color::GREEN,
		Color::MAGENTA,
		Color::RED,
	};

	for (int row = 0; row <= 5; row++)
	{

		for (float center = leftEdge; center <= rightEdge; center += step)
		{
			vec3 ctr = vec3(center, 0.90 - (size * row), 0.0f);
			Rectangle border(ctr, size, borderColor);
			addShape(border);
			Rectangle block(ctr, size - 0.01f, colors[row]);
			addShape(block);
		}
	}


	for (float center = -0.15; center <= 0.15; center += 0.125f)
	{
		Rectangle platformBorder = Rectangle(vec3(center, -0.90f, 0.0f), 0.125f, Color::GREEN);
		m_shapes.push_back(platformBorder);
		Rectangle platform = Rectangle(vec3(center, -0.90f, 0.0f), 0.125f - 0.01f, Color::YELLOW);
		m_shapes.push_back(platform);
	}
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
		else
		{
			shape.resetRotation();
		}

		if (SCALE && &shape == &m_shapes.at(RAND))
		{
			shape.scale(S_FACTOR);
		}
		else
		{
			shape.resetScale();
		}

		if (MOVE && &shape == &m_shapes.at(RAND))
		{
			glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
			shape.moveTo(center);
		}
		else
		{
			shape.resetPosition();
		}

		if (RESET)
		{
			shape.resetScale();
			shape.resetRotation();
			shape.resetPosition();
			RESET = false;
			ROTATE = false;
			SCALE = false;
			MOVE = false;
		}

		m_renderer->getShader().use();
		unsigned int transformLoc = glGetUniformLocation(m_renderer->getShader().ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(shape.getTransform()));
		m_renderer->render(shape.getVAO(), shape.getEBO(), shape.getNumVertices());
	}
}

void App::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_M) && action == GLFW_PRESS)
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
		std::cout << "Rotate: " << (ROTATE ? "true" : "false") << " - at index " << RAND << std::endl;
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		SCALE = !SCALE;
		if (!SCALE)
			S_FACTOR = 1.0f;
		else
			S_FACTOR = 2.5f;
		std::cout << "Scale: " << (SCALE ? "true" : "false") << " - at index " << RAND << std::endl;
		std::cout << "Scale factor: " << S_FACTOR << std::endl;
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		MOVE = !MOVE;
		std::cout << "Move: " << (MOVE ? "true" : "false") << " - at index " << RAND << std::endl;
	}

	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		RESET = !RESET;
		std::cout << "Resetting all shapes" << std::endl;
	}
}

// glfw: viewport to window adjustment
void App::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
