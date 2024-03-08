#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <string>

#include <initializer_list>
#include "../Camera/Perspective/PerspectiveCamera.h"
#include "../Color/Color.h"
#include "../Renderer/Renderer.h"
#include "../Shapes/Circle/Circle.h"
#include "../Shapes/Rectangle/Rectangle.h"
#include "../Shapes/Shape.h"
#include "App.h"

using std::string;
using glm::vec3;

/************DEBUG*************/
static bool NEXT_TEXTURE = false;
static bool RESET_TEXTURE = false;
/************DEBUG*************/

App::App(unsigned int width, unsigned int height, const char* vertextShaderPath, const char* fragmentShaderPath) : m_vertexShaderPath(vertextShaderPath), m_fragmentShaderPath(fragmentShaderPath)
{
	m_renderer = std::make_unique<Renderer>();
	m_renderer->initializeGLFW();
	createWindow(width, height);
	m_renderer->initializeGLAD();
	m_renderer->initializeShader(m_vertexShaderPath, m_fragmentShaderPath);
	initializeShapes();
	initializeCamera();
}

App::~App()
{
	for (Shape* shape : m_shapes)
	{
		delete shape;
	}

	if (m_window)
	{
		glfwDestroyWindow(m_window);
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
	m_window = glfwCreateWindow(screenWidth, screenHeight, "Scene", NULL, NULL);
	if (!m_window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, this);
	glfwSetKeyCallback(m_window, keyCallback);
	glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
	glfwSetCursorPosCallback(m_window, CursorPosCallback);
	glfwSetScrollCallback(m_window, scrollCallback);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

void App::initializeShapes()
{
	/**************************************************/
	/*****************ADD SHAPES HERE******************/
	/**************************************************/
	Color yellow(0.91, 0.84, 0.34);
	Color blue(0.16, 0.45, 0.45);
	Color red(0.66, 0.08, 0.08);
	Color green(0.36, 0.6, 0.11);

	std::initializer_list<const char*> texturePaths = { "assets/box.png", "assets/smilie.png" };

	Rectangle* topRight = new Rectangle(vec3(0.85f, 0.85f, 0.0f), 0.50f, 1.0f, yellow, texturePaths);
	Rectangle* bottomRight = new Rectangle(vec3(0.85f, -0.85f, 0.0f), 0.5f, 1.0f, blue, texturePaths);
	Rectangle* bottomLeft = new Rectangle(vec3(-0.85f, -0.85f, 0.0f), 0.5f, 1.0f, red, texturePaths);
	Rectangle* topLeft = new Rectangle(vec3(-0.85f, 0.85f, 0.0f), 0.5f, 1.0f, green, texturePaths);

	addShape(topRight);
	addShape(bottomRight);
	addShape(bottomLeft);
	addShape(topLeft);
}

void App::initializeCamera()
{
	/**************************************************/
	/*****************ADD CAMERA HERE******************/
	/**************************************************/
	int width, heigth;
	glfwGetFramebufferSize(m_window, &width, &heigth);
	float aspectRatio = (float)width / (float)heigth;
	mat4 projection(1.0f);
	vec3 cameraPos(0.0f, 0.0f, 5.0f);
	vec3 cameraFront(0.0f, 0.0f, -1.0f);
	vec3 cameraUp(0.0f, 1.0f, 0.0f);
	float fov = 45.0f;
	m_camera = std::make_unique<PerspectiveCamera>(projection, cameraPos, cameraFront, cameraUp, fov, aspectRatio);
	dynamic_cast<PerspectiveCamera*>(m_camera.get())->setSpeed(5);
}

void App::gameLoop()
{
	while (!glfwWindowShouldClose(m_window))
	{
		render();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

void App::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	processKeyboardInput();
	m_camera->update();
	m_renderer->getShader().use();
	m_renderer->getShader().setMat4("view", m_camera->getView());
	m_renderer->getShader().setMat4("projection", m_camera->getProjection());

	unsigned int modelLoc = glGetUniformLocation(m_renderer->getShader().ID, "model");
	unsigned int viewLoc = glGetUniformLocation(m_renderer->getShader().ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_camera->getView()));

	for (Shape* shape : m_shapes)
	{
		if (NEXT_TEXTURE)
		{
			shape->applyNextTexture();
		}
		if (RESET_TEXTURE)
		{
			shape->applyTexture(0);
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(shape->getTransform()));
		glUniform1i(glGetUniformLocation(m_renderer->getShader().ID, "hasTexture"), shape->hasTextures());
		shape->render();
	}
	NEXT_TEXTURE = false;
	RESET_TEXTURE = false;
}

void App::processKeyboardInput()
{
	PerspectiveCamera* perspectiveCamera = dynamic_cast<PerspectiveCamera*>(m_camera.get());
	if (perspectiveCamera)
	{
		if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		{
			perspectiveCamera->transform(glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		{
			perspectiveCamera->transform(glm::vec3(0.0f, -1.0f, 0.0f));
		}
		if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		{
			perspectiveCamera->transform(glm::vec3(-1.0f, 0.0f, 0.0f));
		}
		if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		{
			perspectiveCamera->transform(glm::vec3(1.0f, 0.0f, 0.0f));
		}
	}
}

void App::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_M) && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		std::cout << "Exiting the game..." << std::endl;
	}
	if ((key == GLFW_KEY_T) && action == GLFW_PRESS)
	{
		NEXT_TEXTURE = true;
		std::cout << "Applying next texture" << std::endl;
	}
	if ((key == GLFW_KEY_Y) && action == GLFW_PRESS)
	{
		RESET_TEXTURE = true;
		std::cout << "Resetting texture" << std::endl;
	}
}

void App::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
	PerspectiveCamera* perspectiveCamera = dynamic_cast<PerspectiveCamera*>(app->m_camera.get());
	if (perspectiveCamera)
	{
		if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
		{
			perspectiveCamera->setFreeLook(true);
		}
		else
		{
			perspectiveCamera->setFreeLook(false);
		}
	}
}

void App::CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
	PerspectiveCamera* perspectiveCamera = dynamic_cast<PerspectiveCamera*>(app->m_camera.get());
	if (perspectiveCamera && perspectiveCamera->getFreeLook())
	{
		perspectiveCamera->freeLook(xpos, ypos);
	}
}

void App::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
	PerspectiveCamera* perspectiveCamera = dynamic_cast<PerspectiveCamera*>(app->m_camera.get());
	if (perspectiveCamera)
	{
		perspectiveCamera->zoom((float)yoffset);
	}
}

// glfw: viewport to window adjustment
void App::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}