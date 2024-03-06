#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <string>

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
// delta time
static float DELTA_TIME = 0.0f;
static float LAST_FRAME = 0.0f;

// camera
//static glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
//static glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -2.0f);
//static glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// mouse movement
static bool MOVE_CAMERA = false;
static bool isFirstMouseMovement = true;
static float yaw = -90.0f;
static float pitch = 0.0f;

static float FOV = 135.0f;
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
	glfwSetMouseButtonCallback(this->m_window, mouseButtonCallback);
	glfwSetCursorPosCallback(this->m_window, mouseCallback);
	glfwSetScrollCallback(this->m_window, scrollCallback);
	glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);
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

	Rectangle* topRight = new Rectangle(vec3(0.85f, 0.85f, 0.0f), 0.25f, 0.50f, yellow);
	Rectangle* bottomRight = new Rectangle(vec3(0.85f, -0.85f, 0.0f), 0.25f, 0.50f, blue);
	Rectangle* bottomLeft = new Rectangle(vec3(-0.85f, -0.85f, 0.0f), 0.25f, 0.50f, red);
	Rectangle* topLeft = new Rectangle(vec3(-0.85f, 0.85f, 0.0f), 0.25f, 0.50f, green);

	addShape(topRight);
	addShape(bottomRight);
	addShape(bottomLeft);
	addShape(topLeft);
}

void App::initializeCamera()
{
	m_camera = std::make_unique<PerspectiveCamera>(glm::mat4(1.0f), this->m_window, glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//float currentFrame = glfwGetTime();
	//DELTA_TIME = currentFrame - LAST_FRAME;
	//LAST_FRAME = currentFrame;
	//// process camera input
	//// increate the camera speed using the deltaTime
	//float cameraSpeed = 3 * DELTA_TIME;

	//// upward movement
	//if (glfwGetKey(this->m_window, GLFW_KEY_W) == GLFW_PRESS)
	//	cameraPos += cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
	//// downward movement
	//if (glfwGetKey(this->m_window, GLFW_KEY_S) == GLFW_PRESS)
	//	cameraPos -= cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
	//// left movement
	//if (glfwGetKey(this->m_window, GLFW_KEY_A) == GLFW_PRESS)
	//	cameraPos -= cameraSpeed * glm::vec3(1.0f, 0.0f, 0.0f);
	//// right movement
	//if (glfwGetKey(this->m_window, GLFW_KEY_D) == GLFW_PRESS)
	//	cameraPos += cameraSpeed * glm::vec3(1.0f, 0.0f, 0.0f);
	//// zoom out
	//if (glfwGetKey(this->m_window, GLFW_KEY_Q) == GLFW_PRESS)
	//	cameraPos += cameraSpeed * glm::vec3(0.0f, 0.0f, 1.0f);
	//// zoom in
	//if (glfwGetKey(this->m_window, GLFW_KEY_E) == GLFW_PRESS)
	//	cameraPos -= cameraSpeed * glm::vec3(0.0f, 0.0f, 1.0f);

	// get actual window size
	//int width, height;
	//glfwGetFramebufferSize(m_window, &width, &height);
	//// calculate aspect ratio
	//float aspectRatio = (float)width / (float)height;
	//// set up the view matrix
	//glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	//// set up the projection matrix
	//glm::mat4 projection = glm::perspective(glm::radians(FOV), aspectRatio, 0.1f, 100.0f);
	this->m_camera->update();

	m_renderer->getShader().use();
	//m_renderer->getShader().setMat4("view", view);
	m_renderer->getShader().setMat4("view", this->m_camera->getView());
	//m_renderer->getShader().setMat4("projection", projection);
	m_renderer->getShader().setMat4("projection", this->m_camera->getProjection());

	unsigned int modelLoc = glGetUniformLocation(m_renderer->getShader().ID, "model");
	unsigned int viewLoc = glGetUniformLocation(m_renderer->getShader().ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(this->m_camera->getView()));

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
}

void App::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
	PerspectiveCamera* perspectiveCamera = dynamic_cast<PerspectiveCamera*>(app->m_camera.get());
	if (perspectiveCamera) // Check if the dynamic_cast was successful
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

// glfw: viewport to window adjustment
void App::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void App::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
	PerspectiveCamera* perspectiveCamera = dynamic_cast<PerspectiveCamera*>(app->m_camera.get());
	if (perspectiveCamera && perspectiveCamera->getFreeLook()) // Check if the dynamic_cast was successful and if free look mode is enabled
	{
		perspectiveCamera->freeLook(xpos, ypos);
	}
}

void App::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	/*cameraPos.z -= (float)yoffset;
	if (cameraPos.z < 1.0f)
		cameraPos.z = 1.0f;
	if (cameraPos.z > 45.0f)
		cameraPos.z = 45.0f;*/
}
