#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../Camera.h"
#include "PerspectiveCamera.h"

// DEBUG 
static float DELTA_TIME = 0.0f;
static float LAST_FRAME = 0.0f;
// DEBUG
PerspectiveCamera::PerspectiveCamera(mat4 projection, GLFWwindow* window, vec3 cameraPos, vec3 cameraFront, vec3 cameraUp, float fov) : Camera(projection, window)
{
	this->m_cameraPos = cameraPos;
	this->m_cameraFront = cameraFront;
	this->m_cameraUp = cameraUp;
	this->m_fov = fov;
	this->m_freeLook = false;
	this->m_firstMouseMovement = true;
	this->m_yaw = -90.0f;
	this->m_pitch = 0.0f;
}

void PerspectiveCamera::update()
{
	processKeyboardInput();
	// processMouseInput(0, 0);
	this->m_view = glm::lookAt(this->m_cameraPos, this->m_cameraPos + this->m_cameraFront, this->m_cameraUp);
	this->m_projection = glm::perspective(glm::radians(m_fov), getAspectRatio(), 0.1f, 100.0f);
}


const bool PerspectiveCamera::getFreeLook() const
{
	return this->m_freeLook;
}

void PerspectiveCamera::setFreeLook(bool freeLook)
{
	this->m_freeLook = freeLook;
	if (!m_freeLook)
		m_firstMouseMovement = true;
}

void PerspectiveCamera::freeLook(float x, float y)
{
	if (m_freeLook)
		processMouseInput(x, y);
}

float PerspectiveCamera::getAspectRatio()
{
	int width, heigth;
	GLFWwindow* window = this->m_window;
	glfwGetFramebufferSize(window, &width, &heigth);
	return (float)width / (float)heigth;
}

void PerspectiveCamera::processKeyboardInput()
{
	float currentFrame = glfwGetTime();
	DELTA_TIME = currentFrame - LAST_FRAME;
	LAST_FRAME = currentFrame;

	float cameraSpeed = 3 * DELTA_TIME;

	// upward movement
	if (glfwGetKey(this->m_window, GLFW_KEY_UP) == GLFW_PRESS)
		m_cameraPos += cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
	// downward movement
	if (glfwGetKey(this->m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
		m_cameraPos -= cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
	// left movement
	if (glfwGetKey(this->m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
		m_cameraPos -= cameraSpeed * glm::vec3(1.0f, 0.0f, 0.0f);
	// right movement
	if (glfwGetKey(this->m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		m_cameraPos += cameraSpeed * glm::vec3(1.0f, 0.0f, 0.0f);
}

void PerspectiveCamera::processMouseInput(float x, float y)
{
	static float lastX = 0.0f;
	static float lastY = 0.0f;
	if (m_firstMouseMovement)
	{
		lastX = x;
		lastY = y;
		m_firstMouseMovement = false;
	}

	float xoffset = x - lastX;
	float yoffset = lastY - y; // reversed since y-coordinates go from bottom to top
	lastX = x;
	lastY = y;

	float sensitivity = 0.1f; // a ratio that define how sensitive the mouse movement will be
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;
	glm::vec3 front{};
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_cameraFront = glm::normalize(front);
}

