#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLApp.h"

OpenGLApp::OpenGLApp() : screenWidth(1024), screenHeight(768), window(nullptr) {}

OpenGLApp::~OpenGLApp()
{
	cleanup();
}

void OpenGLApp::run()
{
	if (!initializeGLFW())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	if (!createWindow())
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		return;
	}

	if (!initializeGLAD())
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}

	mainLoop();
}

bool OpenGLApp::initializeGLFW()
{
	if (!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	return true;
}

bool OpenGLApp::createWindow()
{
	window = glfwCreateWindow(screenWidth, screenHeight, "SimpleWindowwithColor", nullptr, nullptr);
	return window != nullptr;
}

bool OpenGLApp::initializeGLAD()
{
	glfwMakeContextCurrent(window);
	return gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
}

void OpenGLApp::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void OpenGLApp::mainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		processInput();
		render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void OpenGLApp::cleanup()
{
	if (window)
	{
		glfwDestroyWindow(window);
		window = nullptr;
	}

	glfwTerminate();
}

void OpenGLApp::render()
{
	static const float red[] = { 1.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, red);
}
