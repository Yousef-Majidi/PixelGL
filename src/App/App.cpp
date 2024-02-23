#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "../Color/Color.h"
#include "../Renderer/Renderer.h"
#include "../Shapes/Circle/Circle.h"
#include "../Shapes/Rectangle/Rectangle.h"
#include "../Shapes/Shape.h"
#include "App.h"

using std::string;
using glm::vec3;

/************DEBUG*************/
static bool START = false;
static vec3 VELOCITY = vec3(0.0f, 0.03f, 0.0f);
/************DEBUG*************/

App::App(unsigned int width, unsigned int height, const char* vertextShaderPath, const char* fragmentShaderPath) : m_vertexShaderPath(vertextShaderPath), m_fragmentShaderPath(fragmentShaderPath)
{
	m_renderer = std::make_unique<Renderer>();
	m_renderer->initializeGLFW();
	createWindow(width, height);
	m_renderer->initializeGLAD();
	m_renderer->initializeShader(m_vertexShaderPath, m_fragmentShaderPath);
	initializesShapes();
}

App::~App()
{
	for (Shape* shape : m_shapes)
	{
		delete shape;
	}

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

void App::addShape(Shape* shape)
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

void App::initializesShapes()
{
	/**************************************************/
	/*****************ADD SHAPES HERE******************/
	/**************************************************/
	Color colors[7] = {
		Color(0.91,0.84,0.34),	// yellow
		Color(0.16,0.45,0.45),	// blue
		Color(0.66,0.08,0.08),	// red
		Color(0.36,0.6,0.11),	// green
		Color(0.5,0.05,0.59),	// purple
		Color(1.0,0.52,0.15),	// orange
	};
	vec3 center{};

	// Blocks
	int numBlocksPerRow = 9;
	int numBlocksPerColumn = 6;
	float blockWidth = 0.35f;
	float blockHeight = 0.2f;
	float borderMargin = 0.05f;

	float totalWidth = numBlocksPerRow * blockWidth + (numBlocksPerRow - 1) * borderMargin;
	float totalHeight = numBlocksPerColumn * blockHeight + (numBlocksPerColumn - 1) * borderMargin;

	float startPosX = -1.0f + (2.0f - totalWidth) / 2 + blockWidth / 2;
	float startPosY = 1.0f - (2.0f - totalHeight) / 2 - blockHeight / 2 + 1.2f;

	for (int i = 0; i < numBlocksPerColumn; i++)
	{
		for (int j = 0; j < numBlocksPerRow; j++)
		{
			float centerX = startPosX + j * (blockWidth + borderMargin);
			float centerY = startPosY - i * (blockHeight + borderMargin);
			center = vec3(centerX, centerY, 0.0f);
			addShape(new Rectangle(center, blockHeight, blockWidth, colors[i]));
		}
	}

	// Platform
	center = vec3(0.0f, -1.85f, 0.0f);
	addShape(new Rectangle(center, 0.20, 0.8, colors[3]));		// green border
	addShape(new Rectangle(center, 0.15, 0.75, colors[0]));	// yellow platform

	// Ball
	vec3 loc = vec3(0.0f, -1.68f, 0.0f);
	addShape(new Circle(loc, 0.05f, Color(0.81, 0.02, 0.24)));	// red ball
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
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f);
	m_renderer->getShader().setMat4("projection", projection);
	m_renderer->getShader().use();

	unsigned int modelLoc = glGetUniformLocation(m_renderer->getShader().ID, "model");
	unsigned int viewLoc = glGetUniformLocation(m_renderer->getShader().ID, "view");

	for (Shape* shape : m_shapes)
	{
		if (START && typeid(*shape) == typeid(Circle))
		{
			shape->translate(VELOCITY);
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(shape->getTransform()));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);
		shape->render();
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
		START = !START;
	}
}

// glfw: viewport to window adjustment
void App::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
