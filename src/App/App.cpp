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
GLuint VBO, VAO, EBO;
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

	float leftEdge = -1.90f;
	float rightEdge = 2.0f;
	float size = 0.2f;
	Color colors[7] = {
		Color::YELLOW,
		Color::BLUE,
		Color::CYAN,
		Color::GREEN,
		Color::MAGENTA,
		Color::RED,
		Color::WHITE,
	};

	for (int row = 0; row <= 5; row++)
	{
		for (float pos = leftEdge; pos <= rightEdge; pos += size)
		{
			vec3 center = vec3(pos, 1.90 - (size * row), 0.0f);
			Rectangle border(center, size, colors[6]);
			addShape(border);
			Rectangle block(center, size - 0.01f, colors[row]);
			addShape(block);
		}
	}


	for (float pos = -0.15; pos <= 0.15; pos += 0.125f)
	{
		vec3 center = vec3(pos, -1.90f, 0.0f);
		Rectangle platformBorder = Rectangle(center, 0.125f, Color::GREEN);
		m_shapes.push_back(platformBorder);
		Rectangle platform = Rectangle(center, 0.115f, Color::YELLOW);
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

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f);
	m_renderer->getShader().setMat4("projection", projection);

	for (Rectangle& shape : m_shapes)
	{
		//glm::mat4 view = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
		m_renderer->getShader().use();
		//We specify the uniform variables in the Vertex Shader
		unsigned int modelLoc = glGetUniformLocation(m_renderer->getShader().ID, "model");
		unsigned int viewLoc = glGetUniformLocation(m_renderer->getShader().ID, "view");
		// We pass the variables to the shaders
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(shape.getTransform()));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);
		shape.render();
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
		std::cout << "Moving the ball" << std::endl;
	}
}

// glfw: viewport to window adjustment
void App::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
