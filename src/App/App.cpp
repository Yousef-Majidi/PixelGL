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
static float DELTA_TIME = 0.0f;
static float LAST_FRAME = 0.0f;

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -2.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
// glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
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
	Color yellow(0.91, 0.84, 0.34);
	Color blue(0.16, 0.45, 0.45);
	Color red(0.66, 0.08, 0.08);
	Color green(0.36, 0.6, 0.11);

	Rectangle* topRight = new Rectangle(vec3(0.85f, 0.85f, 0.0f), 0.25f, 0.50f, yellow);
	Rectangle* bottomRight = new Rectangle(vec3(0.85f, -0.85f, 0.0f), 0.25f, 0.50f, blue);
	Rectangle* bottomLeft = new Rectangle(vec3(-0.85f, -0.85f, 0.0f), 0.25f, 0.50f, red);
	Rectangle* topLeft = new Rectangle(vec3(-0.85f, 0.85f, 0.0f), 0.25f, 0.50f, green);

	addShape(topRight);
	addShape(bottomRight);
	addShape(bottomLeft);
	addShape(topLeft);
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
	float currentFrame = glfwGetTime();
	DELTA_TIME = currentFrame - LAST_FRAME;
	LAST_FRAME = currentFrame;
	// process camera input
	// increate the camera speed using the deltaTime
	float cameraSpeed = 3 * DELTA_TIME;

	// upward movement
	if (glfwGetKey(this->m_window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
	// downward movement
	if (glfwGetKey(this->m_window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
	// left movement
	if (glfwGetKey(this->m_window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= cameraSpeed * glm::vec3(1.0f, 0.0f, 0.0f);
	// right movement
	if (glfwGetKey(this->m_window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += cameraSpeed * glm::vec3(1.0f, 0.0f, 0.0f);
	// zoom out
	if (glfwGetKey(this->m_window, GLFW_KEY_Q) == GLFW_PRESS)
		cameraPos += cameraSpeed * glm::vec3(0.0f, 0.0f, 1.0f);
	// zoom in
	if (glfwGetKey(this->m_window, GLFW_KEY_E) == GLFW_PRESS)
		cameraPos -= cameraSpeed * glm::vec3(0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	/*glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f);
	m_renderer->getShader().setMat4("projection", projection);
	m_renderer->getShader().use();*/


	// get actual window size
	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);

	// calculate aspect ratio
	float aspectRatio = (float)width / (float)height;

	// set up the view matrix
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	m_renderer->getShader().use();
	m_renderer->getShader().setMat4("view", view);

	// set up the projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(135.0f), aspectRatio, 0.1f, 100.0f);
	m_renderer->getShader().setMat4("projection", projection);

	unsigned int modelLoc = glGetUniformLocation(m_renderer->getShader().ID, "model");
	unsigned int viewLoc = glGetUniformLocation(m_renderer->getShader().ID, "view");
	// glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	for (Shape* shape : m_shapes)
	{
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(shape->getTransform()));
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
